#!/usr/bin/env python3
import asyncio
import argparse
import time

import stream
import forwarding_parser

async def copy(reader: stream.Stream, writer: stream.Stream):
    buf = b''
    while (data := buf + await reader.read(2**16)):
        buf=b''
        if args.hex == 'encode':
            data = b''.join([f'{0:02x}'.encode() for c in data])
        if args.hex == 'decode':
            if len(data) % 2:
                buf += data[-1:]
                data = data[:-1]
            data = int(data, 16).to_bytes(len(data)//2, 'big')
        writer.write(data)
        await writer.drain()

@stream.streamify
async def connection(server_socket: stream.Stream):
    async with stream.Stream(await asyncio.open_connection(*args.proxy[0])) as client_socket:
        if args.connect is not None:
            client_socket.write(f"CONNECT {args.connect[0][0]}:{args.connect[0][1]} HTTP/1.1\r\nProxy-Connection: Keep-Alive\r\n\r\n".encode())
            await client_socket.drain()
            await client_socket.readuntil(b'\r\n\r\n')
        await asyncio.gather(
            copy(client_socket, server_socket),
            copy(server_socket, client_socket),
        )

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--proxy', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1))
    parser.add_argument('--hex', choices=['encode', 'decode', 'none'], default='none')
    global args
    args = parser.parse_args()

    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

asyncio.run(main())
