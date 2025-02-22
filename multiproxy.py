#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
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
    async def loop(self):
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
        message()

connections : dict[bytes, connection] = {}

class message:
    @staticmethod
    def from_bytes(data: bytes) -> message:
        res : message
        res = pickle.loads(data) # type: ignore
        return res

@stream.streamify
async def inner_callback(inner_sock: stream.Stream):
    data = await inner_sock.recv_msg()
    msg = message.from_bytes(data)
    con = connection.get_by_id(msg.con_id)
    ...


@stream.streamify
async def outer_callback(outer_sock: stream.Stream):
    con_id = random.randbytes(8)
    con = connection(con_id, outer_sock)
    await con.loop()


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True, nargs='*')
    parser.add_argument('--is-server', action='store_true')
    args = parser.parse_args()
    async with await asyncio.start_server(inner_callback if args.is_server else outer_callback, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

