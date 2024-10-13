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
import retry_loop
import timeout

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG)

args = argparse.Namespace()

# signer = sign.Signer(8)
con_id_len = 8

wait_interval = 15 * 10**9
fail_count = wait_interval * 9

class InnerStream:
    def __init__(self, s: stream.Stream):
        self.s = s
    async def send_msg(self, data: bytes) -> None:
        await timeout.run_with_timeout(self.s.send_msg(data), 2)
    async def recv_msg(self) -> bytes:
        return cast(bytes, await timeout.run_with_timeout(self.s.recv_msg(), 4))
    async def safe_close(self) -> None:
        return await self.s.safe_close()

class OuterConnection:
    def __new__(cls, con_id: bytes, *a: Any) -> OuterConnection:
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
            # self.inner_recv_count = 0
            self.chunks : collections.deque[tuple[int, bytes]] = collections.deque()
            assert has_never_seen.has_never_seen(con_id)
            self.sock = stream.Stream(await timeout.run_with_timeout(asyncio.open_connection(*args.connect[0]), 2)) if sock is None else sock
            self.read_task = asyncio.create_task(self.reader_loop())
        if hasattr(self, 'gateway') and self.gateway is not None:
            await self.gateway.safe_close()
        self.gateway : InnerStream | None = gateway
        return self
    async def reader_loop(self) -> None:
        try:
            async with self.sock:
                retry = retry_loop.Retry(wait_interval, fail_count)
                while (data := await self.sock.read(2**16)):
                    chunk = (self.outer_recv_count, data)
                    self.outer_recv_count += 1
                    self.chunks.append(chunk)
                    if len(self.chunks) > 16:
                        self.chunks.popleft()
                    while self.inner_send_count != self.outer_recv_count:
                        while self.gateway is None:
                            logger.debug(f'Waiting...')
                            await asyncio.sleep(0.1)
                            if retry.fail():
                                return
                        for chunk in self.chunks:
                            if chunk[0] == self.inner_send_count:
                                break
                        else:
                            return
                        logger.debug(f'Got data to send inside: {chunk!r}')
                        try:
                            assert self.gateway is not None
                            await self.gateway.send_msg(chunk[0].to_bytes(8, 'big')+chunk[1])
                        except Exception as e:
                            logger.debug(f'Send inside failed with, retrying: {data!r}, {type(e) = }, {e = }')
                            await self.gateway.safe_close()
                            self.gateway = None
                            if retry.fail():
                                return
                        else:
                            logger.debug(f'Successfully sent inside: {chunk!r}')
                            retry.success()
                            self.inner_send_count += 1
        finally:
            outer_connections.pop(self.con_id, None)

    async def writer_loop(self) -> bool:
        assert self.gateway is not None
        try:
            while (chunk := await self.gateway.recv_msg()):
                num, data = int.from_bytes(chunk[:8], 'big'), chunk[8:]
                logger.debug(f'got data to send outside: {(num, data)!r}')
                assert num == self.outer_send_count
                try:
                    await self.sock.safe_write(data)
                except Exception as e:
                    outer_connections.pop(self.con_id, None)
                    logger.debug(f'outer socket is closed: {data!r}, {type(e) = }, {e = }')
                    return False
                self.outer_send_count += 1
                logger.debug(f'successfully send outside: {data!r}')
            return False
        except Exception as e:
            logger.debug(f'inner socket is closed: {type(e) = }, {e = }')
            return True

outer_connections : dict[bytes, OuterConnection] = {} 

import types
types.coroutine

@stream.streamify
async def server_connection(sock_: stream.Stream) -> None:
    sock = InnerStream(sock_)
    try:
        await sock.send_msg(b'hello')
        assert await sock.recv_msg() == b'hello'
        data = await sock.recv_msg()
    except Exception as e:
        logging.debug(f'inner client failed {type(e) = } {e = }')
        return
    con_id, inner_send_count = data[:con_id_len], int.from_bytes(data[con_id_len:], 'big')
    logging.debug(f'inner client connected with {con_id.hex() = }')
    try:
        outer_connection = await OuterConnection(con_id, sock)
        outer_connection.inner_send_count = inner_send_count
        logging.debug(f'sending good for {con_id.hex() = }')
        await sock.send_msg(outer_connection.outer_send_count.to_bytes(8, 'big'))
    except Exception:
        return
    await outer_connection.writer_loop()

async def connect_one(out_q: asyncio.Queue[InnerStream], kill_prev: asyncio.Queue[None], kill_this: asyncio.Queue[None]) -> None:
    try:
        logging.debug(f'_ _ _ opening internal connection...')
        async with stream.Stream(await timeout.run_with_timeout(asyncio.open_connection(*args.connect[0]), 2)) as sock_:
            logging.debug(f'_ _ _ internal connection made.')
            sock = InnerStream(sock_)
            await sock.send_msg(b'hello')
            assert await sock.recv_msg() == b'hello'
            logging.debug(f'_ _ _ header exchange successfull.')
            out_q.put_nowait(sock)
            kill_prev.put_nowait(None)
            await kill_this.get()
    except Exception as e:
        logger.debug(f'_ _ _ inner socket is closed, retrying: {type(e) = }, {e = }')

async def connect_many(out_q: asyncio.Queue[InnerStream]) -> None:
    kill_this : asyncio.Queue[None] = asyncio.Queue()
    while 1:
        kill_prev = kill_this
        kill_this = asyncio.Queue()
        asyncio.create_task(connect_one(out_q, kill_prev, kill_this))
        await asyncio.sleep(8)

@stream.streamify
async def client_connection(sock_: stream.Stream) -> None:
    con_id = random.randbytes(con_id_len)
    logging.debug(f'outer client connected with {con_id.hex() = }')
    outer_connection = await OuterConnection(con_id, None, sock_)
    retry = retry_loop.Retry(wait_interval, fail_count)
    try:
        out_q : asyncio.Queue[InnerStream] = asyncio.Queue()
        asyncio.create_task(connect_many(out_q))
        while 1:
            try:
                logging.debug(f'opening internal connection... {con_id.hex() = }')
                sock = await out_q.get()
                # async with stream.Stream(await timeout.run_with_timeout(asyncio.open_connection(*args.connect[0]), 2)) as sock_:
                logging.debug(f'internal connection made. {con_id.hex() = }')
                # sock = InnerStream(sock_)
                logging.debug(f'senging header... {con_id.hex() = }')
                await sock.send_msg(con_id + outer_connection.outer_send_count.to_bytes(8, 'big'))
                logging.debug(f'header sent. recving headers... {con_id.hex() = }')
                outer_connection.inner_send_count = int.from_bytes(await timeout.run_with_timeout(sock.recv_msg(), 2), 'big')
                logging.debug(f'header recved. {con_id.hex() = }')
                retry.success()
                outer_connection.gateway = sock
                if not await outer_connection.writer_loop():
                    return
            except Exception as e:
                outer_connection.gateway = None
                logger.debug(f'inner socket is closed, retrying: {con_id.hex() = } {type(e) = }, {e = }')
                if retry.fail():
                    return
            await asyncio.sleep(0.1)
    finally:
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

