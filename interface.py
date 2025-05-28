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
import socket

args = argparse.Namespace()

async def copy(r: stream.Stream, w: stream.Stream) -> None:
    while data := await r.safe_read(2**16):
        print(data)
        await w.safe_write(data)

@stream.streamify
async def connection(ls: stream.Stream) -> None:
    data = await ls.safe_readuntil(b'\r\n\r\n')
    protocol, rsock, *_ = data.decode().split()
    print(f'{protocol = } {rsock = }')
    if protocol.lower() != 'connect':
        return
    dest = forwarding_parser.ColonSeparatedSocketSequence(1)(rsock)[0]
#    for ipdest in socket.getaddrinfo(*dest, family=socket.AF_INET, type=socket.SOCK_STREAM, proto=socket.IPPROTO_TCP):
    for ipdest in socket.getaddrinfo(*dest):
        try:
            sock = socket.socket()
            sock.connect(ipdest[-1])
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            SO_BINDTODEVICE: int
            SO_BINDTODEVICE = socket.SO_BINDTODEVICE # type: ignore
            sock.setsockopt(socket.SOL_SOCKET, SO_BINDTODEVICE, args.interface.encode())
            print(ipdest[-1])
            break
        except Exception as e:
            print(type(e), e)
    else:
        print(f'{dest = } no ip.')
    con = await asyncio.open_connection(sock=sock)
    async with stream.Stream(con) as rs:
        await ls.safe_write(b'HTTP/1.1 200 Connection established\r\n\r\n')
        await asyncio.gather(
            copy(ls, rs),
            copy(rs, ls),
        )



async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--interface', type=str, required=True)
    args = parser.parse_args()
    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

