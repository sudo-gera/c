#!/usr/bin/env python3
import asyncio
import argparse
import time

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

async def copy(reader: stream.Stream, writer: stream.Stream, _hex):
    buf = b''
    while (data := buf + await reader.read(2**16)):
        buf=b''
        if _hex == 'encode':
            data = b''.join([f'{c:02x}'.encode() for c in data])
        if _hex == 'decode':
            if len(data) % 2:
                buf += data[-1:]
                data = data[:-1]
            data = int(data, 16).to_bytes(len(data)//2, 'big')
        tasks = []
        while data:
            chunk_size = 256
            chunk = data[:chunk_size]
            data = data[chunk_size:]
            #print(reader, writer, chunk)
            tasks << new << asyncio.create_task(writer.safe_write(chunk))
            await asyncio.sleep(args.sleep)
        await asyncio.gather(*tasks)
        await writer.drain()

@stream.streamify
async def connection(server_socket: stream.Stream):
    try:
        async with stream.Stream(await asyncio.open_connection(*args.proxy[0])) as client_socket:
            if args.connect is not None:
                await client_socket.safe_write(f"CONNECT {args.connect[0][0]}:{args.connect[0][1]} HTTP/1.1\r\nProxy-Connection: Keep-Alive\r\n\r\n".encode())
                await client_socket.readuntil(b'\r\n\r\n')
            await asyncio.gather(
                copy(client_socket, server_socket, args.hex),
                copy(server_socket, client_socket, {'none':'none', 'encode':'decode', 'decode':'encode'}[args.hex]),
            )
    except Exception as e:
        print(type(e), e)
        # raise

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--proxy', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1))
    parser.add_argument('--sleep', type=float, default=0)
    parser.add_argument('--hex', choices=['encode', 'decode', 'none'], default='none')
#    parser.add_argument('--print', action='store true')
    global args
    args = parser.parse_args()

    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

asyncio.run(main())
