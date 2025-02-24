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
import pickle
from collections import deque

args = argparse.Namespace()
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(created)9.7f %(filename)s:%(lineno)d %(message)s')

inside_q : asyncio.Queue[message] = asyncio.Queue(maxsize=0)

class worker:
    def __init__(self):
        self.wait_for_being_enabled : asyncio.Queue[None] = asyncio.Queue()
        self.wait_for_being_disabled : asyncio.Queue[None] = asyncio.Queue()
        self.enabled = False
    async def accept(self, sock: stream.Stream):
        self.wait_for_being_enabled.put_nowait(None)
        await self.step(sock)
    async def main(self):
        while 1:
            await self.wait_for_being_enabled.get()
            try:
                async with stream.Stream(asyncio.open_connection(*random.choice(args.connect)[0])) as sock:
                    await self.step(sock)
                self.wait_for_being_enabled = asyncio.Queue()
            except Exception as e:
                logger.debug(f'Worker failed: {type(e) = }, {e = }')
    async def step(self, sock):
        try:
            self.enabled = True
            asyncio.gather(
                self.recv_loop(sock),
                self.send_loop(sock),
                self.disable_waiter(sock)
            )
        except Exception as e:
            logger.debug(f'Worker step failed: {type(e) = }, {e = }')
        finally:
            self.enabled = False
    async def recv_loop(self, sock: stream.Stream) -> None:
        while 1:
            data = await sock.recv_msg()
            msg = message.from_bytes(data)
            asyncio.create_task(connection.get_by_id(msg.con_id).on_message(msg))
    async def send_loop(self, sock: stream.Stream) -> None:
        while 1:
            msg = await inside_q.get()
            data = msg.to_bytes()
            sock.send_msg(data)
    async def disable_waiter(self):
        await self.wait_for_being_disabled.get()
        raise TabError('disabled.')
    def __await__(self):
        return self.main().__await__()
    def enable(self):
        if self.wait_for_being_enabled.empty():
            self.wait_for_being_enabled.put_nowait(None)
    async def disable(self):
        self.wait_for_being_disabled.put_nowait(None)
        while self.enabled:
            await asyncio.sleep(0.01)

class manager:
    def __init__(self):
        self.workers : list[worker] = [worker() for i in range(args.workers)]
    async def main(self):
        await asyncio.gather([
            self.reloader(),
            self.loader(),
            *self.workers,
        ])
    async def reloader(self):
        for w in self.workers:
            await asyncio.sleep(args.reload_period / len(self.workers))
            await w.disable()
            w.enable()
    async def loader(self):
        while 1:
            await asyncio.sleep(0.1)
            while len([w for w in self.workers if w.enabled]) < args.min_workers:
                random.choice(self.workers).enable()
                await asyncio.sleep(0.01)
    def __await__(self):
        return self.main().__await__()



class connection:
    @staticmethod
    def get_by_id(con_id: bytes) -> connection:
        if con_id not in connections:
            connections[con_id] = connection(con_id)
        return connections[con_id]
    def __init__(self, con_id: bytes, con: stream.Stream | None = None):
        self.con = con
        self.con_id = con_id
        self.outer_recv_count = 0
        self.recved_messages_to_send : list[message] = []
    async def main(self):
        if self.con is None:
            assert False
            # self.con =
        assert self.con is not None
        await asyncio.gather(
            self.reader_loop,
            # self.writer_loop,
        ) 
    async def reader_loop(self):
        assert isinstance(self.con, stream.Stream)
        data = self.con.safe_read(2**16)
        msg = message(data=data, msg_id=self.outer_recv_count, con_id=self.con_id)
        self.outer_recv_count += 1

    def __await__(self):
        return self.main().__await__()

connections : dict[bytes, connection] = {}

class message:
    @staticmethod
    def from_bytes(data: bytes) -> message:
        res : message
        res = pickle.loads(data) # type: ignore
        return res

@stream.streamify
async def inner_callback(inner_sock: stream.Stream):
    await worker().accept(inner_sock)

@stream.streamify
async def outer_callback(outer_sock: stream.Stream):
    con_id = random.randbytes(8)
    con = connection(con_id, outer_sock)
    await con


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True, nargs='*')
    parser.add_argument('--workers', type=int)
    parser.add_argument('--min-workers', type=int)
    parser.add_argument('--reload-period', type=int)
    args = parser.parse_args()
    is_server = not hasattr(args, 'workers')
    if not is_server:
        asyncio.create_task(manager())
    async with await asyncio.start_server(inner_callback if is_server else outer_callback, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

