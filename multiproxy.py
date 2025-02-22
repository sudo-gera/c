#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
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

args = argparse.Namespace()
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(created)9.7f %(filename)s:%(lineno)d %(message)s')


class message:
    @staticmethod
    async def from_stream():
        


@stream.streamify
async def inner_callback(inner_sock: stream.Stream):
    data = await inner_sock.recv_msg()


@stream.streamify
async def outer_callback(outer_sock: stream.Stream):
    con_id = random.randbytes(8).hex()
    


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True, nargs='*')
    parser.add_argument('--is-server', action='store_true')
    args = parser.parse_args()
    async with await asyncio.start_server(server_connection if args.is_server else client_connection, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

