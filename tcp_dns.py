#!/usr/bin/env python3
import asyncio
import argparse
import asyncio.base_tasks
import time
import typing

import stream
import forwarding_parser
import asyncio
import random

args = argparse.Namespace()

popular_dns_servers=[
    forwarding_parser.ColonSeparatedSocketSequence(1)('1.1.1.1:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('8.8.8.8:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('8.8.4.4:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('1.0.0.1:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('95.85.95.85:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('2.56.220.2:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('77.88.8.8:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('77.88.8.1:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('62.76.76.62:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('62.76.62.76:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('195.208.4.1:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('195.208.5.1:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('9.9.9.9:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('9.9.9.10:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('208.67.222.222:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('208.67.220.220:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('208.67.222.220:53'),
    forwarding_parser.ColonSeparatedSocketSequence(1)('208.67.220.222:53'),
]

class UDPConnection(asyncio.DatagramProtocol):

    def connection_made(self, transport: asyncio.BaseTransport) -> None:
        self.transport = typing.cast(asyncio.DatagramTransport, transport)

    async def async_datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        print('got udp client')
        message = len(data).to_bytes(2, 'big') + data
        dns_server = random.choice(args.connect)[0]
        to_connect = args.proxy[0] if args.proxy else dns_server
        print(f'selected {dns_server}')
        async with stream.Stream(asyncio.open_connection(*to_connect)) as tcp_connection:
            if args.proxy:
                await tcp_connection.safe_write((
                    f'CONNECT {dns_server[0]}:{dns_server[1]} HTTP/1.1'+
                    '\r\nProxy-Connection: Keep-Alive\r\n\r\n'
                ).encode())
                await tcp_connection.readuntil(b'\r\n\r\n')
            print('connected')
            await tcp_connection.safe_write(message)
            print('sent')
            data_len = int.from_bytes(await tcp_connection.readexactly(2), 'big')
            data = await tcp_connection.readexactly(data_len)
            print('recved')
        self.transport.sendto(data, addr)
        print('closing client')

    def datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        asyncio.create_task(self.async_datagram_received(data, addr))

@stream.streamify
async def TCPConnection(sock: stream.Stream):
    print('got tcp client')
    data_len = int.from_bytes(await sock.readexactly(2), 'big')
    data = await sock.readexactly(data_len)
    message = len(data).to_bytes(2, 'big') + data
    async with stream.Stream(asyncio.open_connection(*random.choice(args.connect)[0])) as tcp_connection:
        print('connected')
        await tcp_connection.safe_write(message)
        print('sent')
        data_len = int.from_bytes(await tcp_connection.readexactly(2), 'big')
        data = await tcp_connection.readexactly(data_len)
        print('recved')
    message = len(data).to_bytes(2, 'big') + data
    await sock.safe_write(message)
    print('closing client')

async def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), nargs='*')
    parser.add_argument('--proxy', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=False)
    global args
    args = parser.parse_args()
    if not args.connect:
        args.connect = popular_dns_servers


    endpoint, _ = await asyncio.get_running_loop().create_datagram_endpoint(
        UDPConnection,
        args.listen[0],
    )

    try:
        async with await asyncio.start_server(TCPConnection, *args.listen[0]) as server:
            await server.serve_forever()
    finally:
        endpoint.close()

if __name__ == '__main__':
    asyncio.run(main())

