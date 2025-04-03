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
import operator
import typing
from collections import deque

args = argparse.Namespace()
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(created)9.7f %(filename)s:%(lineno)d %(message)s')

inside_q : asyncio.Queue[message] = asyncio.Queue(maxsize=0)

class sleeper:
    def __init__(self) -> None:
        self.q : asyncio.Queue[None] = asyncio.Queue()
    def __call__(self) -> None:
        if self.q.empty():
            self.q.put_nowait(None)
    def __await__(self) -> typing.Any:
        self.q = asyncio.Queue()
        return self.q.get().__await__()

class worker:
    def __init__(self) -> None:
        self.wake_main = sleeper()
        self.wake_disabler = sleeper()
        self.enabled = False
    async def accept(self, sock: stream.Stream) -> None:
        self.wake_main()
        await self.step(sock)
    async def main(self) -> None:
        while 1:
            await self.wake_main
            try:
                async with stream.Stream(asyncio.open_connection(*random.choice(args.connect)[0])) as sock:
                    await self.step(sock)
            except Exception as e:
                logger.debug(f'Worker failed: {type(e) = }, {e = }')
    async def step(self, sock: stream.Stream) -> None:
        try:
            self.enabled = True
            asyncio.gather(
                self.recv_loop(sock),
                self.send_loop(sock),
                self.disable_waiter()
            )
        except Exception as e:
            logger.debug(f'Worker step failed: {type(e) = }, {e = }')
        finally:
            self.enabled = False
    async def recv_loop(self, sock: stream.Stream) -> None:
        while 1:
            data = await sock.recv_msg()
            msg = message.from_bytes(data)
            asyncio.create_task(connection.get_by_id(msg.con_id).on_msg(msg))
    async def send_loop(self, sock: stream.Stream) -> None:
        while 1:
            msg = await inside_q.get()
            data = msg.to_bytes()
            await sock.send_msg(data)
    async def disable_waiter(self) -> None:
        await self.wake_disabler
        raise TabError('disabled.')
    def __await__(self) -> typing.Any:
        return self.main().__await__()
    def enable(self) -> None:
        self.wake_main()
    async def disable(self) -> None:
        self.wake_disabler()
        while self.enabled:
            await asyncio.sleep(0.01)

class manager:
    def __init__(self) -> None:
        self.workers : list[worker] = [worker() for i in range(args.workers)]
    async def main(self) -> None:
        await asyncio.gather(
            self.reloader(),
            self.loader(),
            *self.workers,
        )
    async def reloader(self) -> None:
        for w in self.workers:
            await asyncio.sleep(args.reload_period / len(self.workers))
            await w.disable()
            w.enable()
    async def loader(self) -> None:
        while 1:
            await asyncio.sleep(0.1)
            while len([w for w in self.workers if w.enabled]) < args.min_workers:
                random.choice(self.workers).enable()
                await asyncio.sleep(0.01)
    def __await__(self) -> typing.Any:
        return self.main().__await__()



class connection:
    @staticmethod
    def get_by_id(con_id: int) -> connection:
        if con_id not in connections:
            connections[con_id] = connection(con_id)
        return connections[con_id]
    class inside:
        def __init__(self, con: connection) -> None:
            self.con = con
            self.sock = con.sock
            self.con_id = con.con_id
            self.outer_recv_count = 0
            self.tasks : list[tuple[float, message]] = []
            self.wake_executor = sleeper()
            self.wake_recver = sleeper()
        
        def put_task(self, at: float, msg: message) -> None:
            self.tasks.append((at, msg))
            self.wake_executor()
        
        async def main(self) -> None:
            asyncio.gather(
                self.inner_sender(),
                self.outer_recver(),
            )

        async def inner_sender(self) -> None:
            assert self.sock is not None
            while 1:
                self.tasks.sort(key=operator.itemgetter(0))
                while self.tasks and self.tasks[0][0] < time.time():
                    msg = self.tasks[0][1]
                    await inside_q.put(msg)
                    self.tasks[0] = time.monotonic() + args.resend_delay
                    self.tasks.sort(key=operator.itemgetter(0))
                await self.wake_executor
        
        async def outer_recver(self) -> None:
            assert self.sock is not None
            while 1:
                while len(self.tasks) < args.max_buffer:
                    data = await self.sock.safe_read(2**16)
                    msg = message(data=data, msg_id=self.outer_recv_count, con_id=self.con_id)
                    self.put_task(time.monotonic(), msg)
                await self.wake_recver
        
        async def on_msg(self, msg: message) -> None:
            self.tasks = [t for t in self.tasks if t[1].msg_id != msg.msg_id]
            self.wake_recver()

        def __await__(self) -> typing.Any:
            return self.main().__await__()

    class outside:
        def __init__(self, con: connection) -> None:
            self.con = con
            self.con_id = con.con_id
            self.sock = con.sock
            self.sent_outside_count = 0
            self.chunks : dict[int, data_message] = {}
            self.should_reply : list[int] = []
            self.wake_sender = sleeper()
            self.wake_replyer = sleeper()
        async def on_msg(self, msg: data_message) -> None:
            if msg.msg_id >= self.sent_outside_count:
                self.chunks[msg.msg_id] = msg
                self.wake_sender()
            self.should_reply = [msg_id for msg_id in self.should_reply if msg_id != msg.msg_id] + [msg.msg_id]
            self.wake_replyer()
        async def outer_sender(self) -> None:
            assert self.sock is not None
            while 1:
                while self.sent_outside_count in self.chunks:
                    msg = self.chunks.pop(self.sent_outside_count)
                    await self.sock.safe_write(msg.data)
                    self.sent_outside_count += 1
                await self.wake_sender
        async def inner_replyer(self) -> None:
            assert self.sock is not None
            while 1:
                while self.should_reply:
                    msg_id = self.should_reply[0]
                    await inside_q.put( (msg_id=msg_id, con_id=self.con_id))
                    self.should_reply[:1] = []
                await self.wake_replyer
        async def main(self) -> None:
            await asyncio.gather(
                self.inner_replyer(),
                self.outer_sender()
            )

    def __init__(self, con_id: int, sock: stream.Stream | None = None) -> None:
        self.sock = sock
        self.con_id = con_id
        self.inside_worker = self.inside(self)
        self.outside_worker = self.outside(self)
    async def main(self) -> None:
        if self.con is None:
            assert False
            # self.con =
        assert self.con is not None
        await asyncio.gather(
            self.inside_worker.main(),
            self.outside_worker.main()
        )
    def __await__(self) -> typing.Any:
        return self.main().__await__()

    async def on_msg(self, msg: message) -> None:
        if msg.data is None:
            await self.outside_worker.on_msg(msg)
        else:
            await self.inside_worker.on_msg(msg)

connections : dict[int, connection] = {}

# class message:
#     @staticmethod
#     def from_bytes(data: bytes) -> message:
#         res : message
#         res = pickle.loads(data) # type: ignore
#         return res
#     def to_bytes(self) -> bytes:
#         return pickle.dumps(self)

class data_message:
    def __init__(self, msg_id: int, con_id: int, data: bytes):
        self.msg_id = msg_id
        self.con_id = con_id
        self.data = data
    def to_bytes(self):
        self.con_id.to_bytes

class delivery_status_message(message):
    def __init__(self, con_id: int, msg_ids: list[int]):
        self.msg_id = msg_id
        self.con_id = con_id

@stream.streamify
async def inner_callback(inner_sock: stream.Stream) -> None:
    await worker().accept(inner_sock)

@stream.streamify
async def outer_callback(outer_sock: stream.Stream) -> None:
    con_id = random.randint(0, 2**63-1) * 2
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
    parser.add_argument('--resend-delay', type=float)
    parser.add_argument('--max-chunks', type=int)
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

