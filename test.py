#!/usr/bin/env python3
import asyncio
import argparse
import time
import random
import sys

import stream
import forwarding_parser

class New:
    def __rlshift__(self, oth):
        self.left = oth
        self.work()
        return self
    def __lshift__(self, oth):
        self.right = oth
        self.work()
        return self
    def work(self):
        try:
            self.left
            self.right
        except AttributeError:
            return
        self.left.append(self.right)

new = New()

async def copy(reader: stream.Stream, writer: stream.Stream, c2s):
    lt = 0
    while (data := await reader.read(2**16)):
        t = time.time_ns()/10**7
        eb='\x1b['
        l = len(data)
        if 1 and (l != 36 or not 1.8 < t - lt < 3 or 1):
            print(f'{t:022.7f}{eb}{c2s*100}C{eb}{random.Random((l)).randint(31,38)}m{l:07d}     {t:022.7f}  {t-lt:022.7f}')
        await writer.safe_write(data)
        lt = t

@stream.streamify
async def connection(server_socket: stream.Stream):
    try:
        async with stream.Stream(await asyncio.open_connection(*args.proxy[0])) as client_socket:
            await asyncio.gather(
                copy(client_socket, server_socket, False),
                copy(server_socket, client_socket, True),
            )
    except Exception as e:
        print(type(e), e)
        # raise

# async def pinger():
#     while 1:
#         await asyncio.sleep(0.002)
#         t=time.time_ns()/10**6
#         print('\x1b[s\r\x1b[99C'+f'{t:022.6f}'+'\x1b[u',end='')
#         sys.stdout.flush()

async def main():
    # asyncio.create_task(pinger())
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--proxy', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    global args
    args = parser.parse_args()

    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

asyncio.run(main())
