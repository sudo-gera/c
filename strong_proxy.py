from __future__ import annotations
import asyncio
import argparse
import forwarding_parser
import stream
import sign
import random
from typing import *
import logging
import functools
import has_never_seen
import time
import bisect
import collections
import timeout
from collections import deque

class Retry:
    def __init__(self, interval: int):
        self.interval = interval
        self.last_success = time.time_ns()
    
    def fail(self) -> bool:
        ct = time.time_ns()
        return self.interval + self.last_success < ct
    
    def success(self) -> None:
        self.last_success = time.time_ns()
    


logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(filename)s:%(lineno)d %(funcName)s %(message)s')

args = argparse.Namespace()

con_id_len = 8

wait_interval = 15 * 10**9

class InnerStream:
    def __init__(self, s: stream.Stream):
        self.s = s
    async def _send_msg(self, data: bytes) -> None:
        try:
            await self.s.send_msg(data)
        except Exception as e:
            logger.debug(f'inner socket raised exc: {type(e) = }, {e = }')
    async def send_msg(self, data: bytes) -> None:
        await timeout.run_with_timeout(self._send_msg(data), 2)
    async def _recv_msg(self) -> bytes | None:
        try:
            return await self.s.recv_msg()
        except Exception as e:
            logger.debug(f'inner socket raised exc: {type(e) = }, {e = }')
            return None
    async def recv_msg(self) -> bytes:
        data = cast(bytes, await timeout.run_with_timeout(self._recv_msg(), 4))
        assert isinstance(data, bytes)
        return data
    async def safe_close(self) -> None:
        return await self.s.safe_close()
    async def __aenter__(self) -> InnerStream:
        await self.s.__aenter__()
        return self
    async def __aexit__(self, *a: Any) -> None:
        await self.s.__aexit__(self, *a)

class OuterConnection:
    def __new__(cls, con_id: bytes, *__: Any, **_: Any) -> OuterConnection:
        if con_id not in outer_connections:
            outer_connections[con_id] = super().__new__(cls)
        self = outer_connections[con_id]
        return self
    def __init__(self, con_id: bytes, gateway: InnerStream | None, sock: stream.Stream | None = None):
        self._awaiter = self._ainit(con_id, gateway, sock).__await__
    def __await__(self) -> Generator[Any, Any, OuterConnection]:
        return self._awaiter()
    async def _ainit(self, con_id: bytes, gateway: InnerStream | None, sock: stream.Stream | None) -> OuterConnection:
        self.con_id = con_id
        if not hasattr(self, 'sock'):
            self.outer_send_count = 0
            self.outer_recv_count = 0
            self.inner_send_count = 0
            self.chunks : collections.deque[tuple[int, bytes]] = collections.deque()
            assert has_never_seen.has_never_seen(con_id)
            self.sock = stream.Stream(await timeout.run_with_timeout(asyncio.open_connection(*args.connect[0]), 2)) if sock is None else sock
            self.read_task = asyncio.create_task(self.reader_loop())
        if hasattr(self, 'gateway') and self.gateway is not None:
            await self.gateway.safe_close()
        self.gateway : InnerStream | None = gateway
        return self
    async def reader_loop(self) -> None:
        con_id = self.con_id
        try:
            async with self.sock:
                retry = Retry(wait_interval)
                while (data := await self.sock.read(2**16)):
                    chunk = (self.outer_recv_count, data)
                    self.outer_recv_count += 1
                    self.chunks.append(chunk)
                    if len(self.chunks) > 16:
                        self.chunks.popleft()
                    while self.inner_send_count != self.outer_recv_count:
                        if self.gateway is None:
                            logger.debug(f'{con_id.hex() = } Start waiting for gateway...')
                            while self.gateway is None:
                                await asyncio.sleep(0.1)
                                if retry.fail():
                                    return
                            logger.debug(f'{con_id.hex() = } Got gateway.')
                        for chunk in self.chunks:
                            if chunk[0] == self.inner_send_count:
                                break
                        else:
                            return
                        logger.debug(f'{con_id.hex() = } Trying to send inside {chunk[0] = }')
                        try:
                            assert self.gateway is not None
                            await self.gateway.send_msg(chunk[0].to_bytes(8, 'big')+chunk[1])
                        except Exception as e:
                            logger.debug(f'{con_id.hex() = } Send inside failed {chunk[0] = } {type(e) = }, {e = }')
                            await self.gateway.safe_close()
                            self.gateway = None
                            if retry.fail():
                                return
                        else:
                            logger.debug(f'{con_id.hex() = } Sent inside. {chunk[0] = }')
                            retry.success()
                            self.inner_send_count += 1
        finally:
            logger.debug(f'{con_id.hex() = } Closing outer connection.')
            outer_connections.pop(self.con_id, None)

    async def writer_loop(self) -> bool:
        con_id = self.con_id
        assert self.gateway is not None
        async with self.gateway:
            try:
                while (chunk := await self.gateway.recv_msg()):
                    num, data = int.from_bytes(chunk[:8], 'big'), chunk[8:]
                    logger.debug(f'{con_id.hex() = } Got data to send outside: {num = }')
                    assert num == self.outer_send_count
                    try:
                        await self.sock.safe_write(data)
                    except Exception as e:
                        outer_connections.pop(self.con_id, None)
                        logger.debug(f'{con_id.hex() = } Outer socket is closed: {type(e) = }, {e = }')
                        return False
                    self.outer_send_count += 1
                    logger.debug(f'{con_id.hex() = } Sent outside {num = }')
                return False
            except Exception as e:
                logger.debug(f'{con_id.hex() = } inner socket is closed: {type(e) = }, {e = }')
                return True

outer_connections : dict[bytes, OuterConnection] = {} 

import types
types.coroutine

@stream.streamify
async def server_connection(sock_: stream.Stream) -> None:
    sock = InnerStream(sock_)
    try:
        data = await sock.recv_msg()
    except Exception as e:
        logger.debug(f'inner client failed {type(e) = } {e = }')
        return
    con_id, inner_send_count = data[:con_id_len], int.from_bytes(data[con_id_len:], 'big')
    logger.debug(f'{con_id.hex() = } New inner client connected.')
    try:
        outer_connection = await OuterConnection(con_id, gateway=sock)
        outer_connection.inner_send_count = inner_send_count
        await sock.send_msg(outer_connection.outer_send_count.to_bytes(8, 'big'))
    except Exception:
        return
    await outer_connection.writer_loop()


@stream.streamify
async def client_connection(sock_: stream.Stream) -> None:
    con_id = random.randbytes(con_id_len)
    logger.debug(f'{con_id.hex() = } New outer client connected.')
    outer_connection = await OuterConnection(con_id, gateway=None, sock=sock_)
    retry = Retry(wait_interval)
    try:
        while 1:
            try:
                logger.debug(f'{con_id.hex() = } opening internal connection...')
                async with stream.Stream(await timeout.run_with_timeout(asyncio.open_connection(*args.connect[0]), 2)) as sock_:
                    logger.debug(f'{con_id.hex() = } internal connection made.')
                    sock = InnerStream(sock_)
                    logger.debug(f'{con_id.hex() = } senging header...')
                    await sock.send_msg(con_id + outer_connection.outer_send_count.to_bytes(8, 'big'))
                    logger.debug(f'{con_id.hex() = } header sent. recving headers...')
                    outer_connection.inner_send_count = int.from_bytes(await sock.recv_msg(), 'big')
                    logger.debug(f'{con_id.hex() = } header recved.')
                    retry.success()
                    outer_connection.gateway = sock
                    if not await outer_connection.writer_loop():
                        return
            except Exception as e:
                assert outer_connection.gateway is sock or outer_connection.gateway is None
                outer_connection.gateway = None
                logger.debug(f'{con_id.hex() = } Inner socket is closed, retrying: {type(e) = }, {e = }')
                if retry.fail():
                    return
            await asyncio.sleep(0.1)
    finally:
        logger.debug(f'{con_id.hex() = } Closing outer connection.')
        outer_connections.pop(con_id, None)


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--is-server', action='store_true')
    args = parser.parse_args()
    async with await asyncio.start_server(server_connection if args.is_server else client_connection, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

