#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
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
import traceback
from collections import deque

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(created)9.7f %(filename)s:%(lineno)d %(message)s')

class Retry:
    def __init__(self, interval: int, con_id: bytes):
        self.interval = interval
        self.con_id = con_id
        self.last_success = time.time_ns()
        # logger.debug(f'{con_id.hex()!r} {id(self)} Setup new retry at {self.last_success}')
    
    def fail(self) -> bool:
        ct = time.time_ns()
        con_id = self.con_id
        value = self.interval + self.last_success < ct
        if value:
            logger.debug(f'{con_id.hex()!r} {id(self)} Failure {self.last_success} < {ct} < {self.last_success + self.interval}')
        return value
    
    def success(self) -> None:
        con_id = self.con_id
        self.last_success = time.time_ns()
        logger.debug(f'{con_id.hex()!r} {id(self)} Success at {self.last_success}')
    



args = argparse.Namespace()

con_id_len = 8

wait_interval = 60 * 10**9

def get_part(data: bytes) -> str:
    try:
        part = data.decode()
    except Exception:
        part = ''
    part = (part.splitlines() + [''])[0][:160]
    part = part if part.isprintable() else ''
    return part

class InnerStream:
    async def send_msg(self, data: bytes) -> None:
        return await timeout.run_with_timeout(self.s.send_msg(data), 2)
    async def recv_msg(self, timeout_:int=300) -> bytes:
        return await timeout.run_with_timeout(self.s.recv_msg(), timeout_)

    def __init__(self, s: stream.Stream):
        self.s = s
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
    def __init__(self, con_id: bytes, gateway: tuple[InnerStream, asyncio.Queue[None]] | None, sock: stream.Stream | None = None):
        self._awaiter = self._ainit(con_id, gateway, sock).__await__
    def __await__(self) -> Generator[Any, Any, OuterConnection]:
        return self._awaiter()
    async def _ainit(self, con_id: bytes, gateway: tuple[InnerStream, asyncio.Queue[None]] | None, sock: stream.Stream | None) -> OuterConnection:
        self.con_id = con_id
        if not hasattr(self, 'sock'):
            assert has_never_seen.has_never_seen(con_id), 'duplicate connection'
            self.outer_send_count = 0
            self.outer_recv_count = 0
            self.inner_send_count = 0
            self.outer_recv_reached_EOF_at : None | int = None
            self.inner_send_reached_EOF = False
            self.chunks : collections.deque[tuple[int, bytes]] = collections.deque()
            self.retry = Retry(wait_interval, self.con_id)
            self.sock = stream.Stream(await asyncio.open_connection(*args.connect[0][0])) if sock is None else sock
            self.read_task = asyncio.create_task(self.main_loop())
        self.gateway : tuple[InnerStream, asyncio.Queue[None]] | None
        if hasattr(self, 'gateway') and self.gateway is not None:
            await self.gateway[0].safe_close()
        self.gateway = gateway
        return self

    def check_for_eof(self) -> None:
        con_id = self.con_id
        if self.inner_send_count == self.outer_recv_reached_EOF_at:
            self.inner_send_reached_EOF = True
            logger.debug(f'{con_id.hex()!r} Data is sent including EOF.')

    async def main_loop(self) -> None:
        con_id = self.con_id
        logger.debug(f'{con_id.hex()!r} Starting main loop.')
        try:
            async with self.sock:
                await asyncio.gather(
                    self.reader_loop(),
                    self.writer_loop(),
                    self.rm_dangling_loop(),
                    self.pinger_loop(),
                )
        except Exception as e:
            logger.debug(f'{con_id.hex()!r} Closing outer connection. {type(e) = }, {e = }')
        else:
            logger.debug(f'{con_id.hex()!r} Closing outer connection.')
        finally:
            if self.gateway is not None:
                self.gateway[1].put_nowait(None)
            outer_connections.pop(self.con_id, None)

    async def rm_dangling_loop(self) -> None:
        while 1:
            await asyncio.sleep(30)
            assert not self.retry.fail(), 'Too long time without data'

    async def get_gateway(self) -> tuple[InnerStream, asyncio.Queue[None]]:
        con_id = self.con_id
        if self.gateway is None:
            logger.debug(f'{con_id.hex()!r} Start waiting for gateway...')
            while self.gateway is None:
                await asyncio.sleep(0.1)
                if self.retry.fail():
                    logger.debug(f'{con_id.hex()!r} Waiting for gateway timed out.')
                    raise TabError('Waiting for timed out.')
        logger.debug(f'{con_id.hex()!r} Got gateway.')
        assert self.gateway is not None
        return self.gateway

    async def send_to_gateway(self, gateway: tuple[InnerStream, asyncio.Queue[None]], data: bytes) -> None:
        con_id = self.con_id
        try:
            await gateway[0].send_msg(data)
        except Exception as e:
            gateway[1].put_nowait(None)
            if self.gateway is gateway:
                self.gateway = None
            logger.debug(f'{con_id.hex()!r} Send inside failed {type(e) = }, {e = }')
            if self.retry.fail():
                logger.debug(f'{con_id.hex()!r} Too may attempts to send inside.')
                raise TabError('Too may attempts to send inside.')

    async def pinger_loop(self) -> None:
        while 1:
            await asyncio.sleep(15)
            gateway = await self.get_gateway()
            await self.send_to_gateway(gateway, (2**64-1).to_bytes(8, 'big') + self.outer_send_count.to_bytes(8, 'big'))

    async def reader_loop(self) -> None:
        con_id = self.con_id
        while 1:
            try:
                if self.outer_recv_reached_EOF_at is not None:
                    if self.inner_send_reached_EOF:
                        logger.debug(f'{con_id.hex()!r} Stop reader loop.')
                        return
                    await asyncio.sleep(1)
                else:
                    data = await self.sock.safe_read(2**16)
            except Exception as e:
                logger.debug(f'{con_id.hex()!r} Outer socket is closed: {type(e) = }, {e = }')
                raise

            if self.outer_recv_reached_EOF_at is None:
                if not data:
                    logger.debug(f'{con_id.hex()!r} EOF is reached while reading outer connection.')
                    self.outer_recv_reached_EOF_at = self.outer_recv_count

                chunk = (self.outer_recv_count, data)
                self.outer_recv_count += 1

                self.chunks.append(chunk)

            while self.inner_send_count != self.outer_recv_count:
                gateway = await self.get_gateway()
                assert gateway is not None, 'no gateway'
                for chunk in self.chunks:
                    if chunk[0] == self.inner_send_count:
                        break
                else:
                    logger.debug(f'{con_id.hex()!r} {self.inner_send_count = } Requested chunk is not found.')
                    raise TabError('Requested chunk is not found.')
                logger.debug(f'{con_id.hex()!r} Trying to send inside {chunk[0] = } {get_part(chunk[1])}')
                data = chunk[0].to_bytes(8, 'big')+chunk[1]
                await self.send_to_gateway(gateway, data)
                logger.debug(f'{con_id.hex()!r} Sent inside. {chunk[0] = }')
                self.retry.success()
                self.inner_send_count += 1

    async def writer_loop(self) -> None:
        con_id = self.con_id
        while 1:
            gateway = await self.get_gateway()
            assert gateway is not None, 'no gateway'

            try:
                data = await gateway[0].recv_msg()
            except Exception as e:
                logger.debug(f'{con_id.hex()!r} Recv inside failed {type(e) = }, {e = }')
                gateway[1].put_nowait(None)
                if gateway is self.gateway:
                    self.gateway = None
                continue

            chunk = num, data = int.from_bytes(data[:8], 'big'), data[8:]
            logger.debug(f'{con_id.hex()!r} Got data to send outside: {num = } {get_part(chunk[1])}')
            if num == 2**64 - 1:
                inner_send_count = int.from_bytes(data[:8], 'big')
                logger.debug(f'{con_id.hex()!r} inner socket already has received {inner_send_count} chunks.')
                while len(self.chunks) > 1 and self.chunks[0][0] < inner_send_count:
                    self.chunks.popleft()
                continue

            try:
                assert num == self.outer_send_count, 'received wrong packet'
                await self.sock.safe_write(data)
            except Exception as e:
                logger.debug(f'{con_id.hex()!r} Outer socket is closed: {type(e) = }, {e = }')
                raise
            else:
                self.outer_send_count += 1
                logger.debug(f'{con_id.hex()!r} Sent outside {num = }')

            if not data:
                logger.debug(f'{con_id.hex()!r} Received inner connection EOF.')
                await self.sock.safe_write_eof()
                logger.debug(f'{con_id.hex()!r} Stop writer loop.')
                return

outer_connections : dict[bytes, OuterConnection] = {} 

@stream.streamify
async def server_connection(sock_: stream.Stream) -> None:
    sock = InnerStream(sock_)
    try:
        await sock.send_msg(b'hello')
        assert b'hello' == await sock.recv_msg()
    except Exception as e:
        logger.debug(f'inner client failed {type(e) = } {e = }')

    try:
        data = await sock.recv_msg()
    except Exception as e:
        logger.debug(f'inner client failed {type(e) = } {e = }')
        return
    con_id, inner_send_count = data[:con_id_len], int.from_bytes(data[con_id_len:], 'big')
    logger.debug(f'{con_id.hex()!r} New inner client connected.')

    try:
        gateway_queue : asyncio.Queue[None] = asyncio.Queue()
        outer_connection = await OuterConnection(con_id, gateway=(sock, gateway_queue))
        outer_connection.inner_send_count = inner_send_count
        outer_connection.check_for_eof()
        await sock.send_msg(outer_connection.outer_send_count.to_bytes(8, 'big'))
    except Exception as e:
        logger.debug(f'{con_id.hex()!r} inner client failed {type(e) = } {e = }')
        return
    await gateway_queue.get()


async def one_client_connection(con_id: bytes, outer_connection: OuterConnection, on_done: list[None], connect: list[tuple[str, int]]) -> None:
    logger.debug(f'{con_id.hex()!r} opening internal connection...')
    try:
        con_pair = await timeout.run_with_timeout(asyncio.open_connection(*connect[0]), 2)
    except Exception as e:
        logger.debug(f'inner client failed {connect[0] = } {type(e) = } {e = }')
        return
    logger.debug(f'{con_id.hex()!r} created internal socket for {connect[0] = }')
    async with stream.Stream(con_pair) as sock_:
        sock = InnerStream(sock_)
        0;                                          logger.debug(f'{con_id.hex()!r} internal connection made, sending hello')
        try:
            await sock.send_msg(b'hello')
            assert b'hello' == await sock.recv_msg(timeout_=2)
            0;                                          logger.debug(f'{con_id.hex()!r} hello recved.')
        except Exception as e:
            logger.debug(f'inner client failed {connect[0] = } {type(e) = } {e = }')
            return

        if on_done:
            0;                                          logger.debug(f'{con_id.hex()!r} another client connected.')
            return
        on_done.append(None)

        0;                                          logger.debug(f'{con_id.hex()!r} senging header...')
        await sock.send_msg(con_id + outer_connection.outer_send_count.to_bytes(8, 'big'))
        0;                                          logger.debug(f'{con_id.hex()!r} header sent. recving headers...')
        outer_connection.inner_send_count = int.from_bytes(await sock.recv_msg(timeout_=4), 'big')
        outer_connection.check_for_eof()
        0;                                          logger.debug(f'{con_id.hex()!r} header recved.')
        gateway_queue : asyncio.Queue[None] = asyncio.Queue()
        outer_connection.gateway = (sock, gateway_queue)
        await gateway_queue.get()

# @stream.streamify
async def client_connection(r: asyncio.StreamReader, w: asyncio.StreamWriter) -> None:
    sock_ = stream.Stream(r,w)
    con_id = random.randbytes(con_id_len)
    logger.debug(f'{con_id.hex()!r} New outer client connected.')
    outer_connection = await OuterConnection(con_id, gateway=None, sock=sock_)
    retry = Retry(wait_interval, con_id)
    while 1:
        try:
            con_count = 4
            await asyncio.gather(
                *map(
                    one_client_connection,
                    [con_id]*con_count,
                    [outer_connection]*con_count,
                    [[]]*con_count,
                    [random.choice(args.connect) for i in range(con_count)],
                )
            )
            retry.success()
        except Exception as e:
            outer_connection.gateway = None
            logger.debug(f'{con_id.hex()!r} Inner socket is closed, retrying: {type(e) = }, {e = }')
            # print(traceback.format_exc())
            if retry.fail():
                logger.debug(f'{con_id.hex()!r} Too may attempts to reopen inner socket.')
                return
        await asyncio.sleep(0.1)
        if con_id not in outer_connections:
            logger.debug(f'{con_id.hex()!r} Stop inner socket loop.')
            return

prev_outer_connections : list[bytes] = []
async def log() -> None:
    while 1:
        await asyncio.sleep(1)
        logger.info(f'connections state:\n'+''.join(
            [
                '?' if k not in outer_connections else ('+' if outer_connections[k].gateway is not None else '-')
                for k in prev_outer_connections
            ] + [
                '+' if c.gateway is not None else '-'
                for k, c in outer_connections.items()
                if k not in prev_outer_connections
            ]
        ))
        prev_outer_connections.clear()
        prev_outer_connections.extend(outer_connections.keys())
        


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True, nargs='*')
    parser.add_argument('--is-server', action='store_true')
    args = parser.parse_args()
    print(args)
    asyncio.create_task(log())
    async with await asyncio.start_server(server_connection if args.is_server else client_connection, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

