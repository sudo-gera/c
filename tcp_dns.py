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

class UDPConnection(asyncio.DatagramProtocol):

    def connection_made(self, transport: asyncio.BaseTransport) -> None:
        self.transport = typing.cast(asyncio.DatagramTransport, transport)

    async def async_datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        print('got udp client')
        message = len(data).to_bytes(2, 'big') + data
        async with stream.Stream(asyncio.open_connection(*random.choice(args.connect)[0])) as tcp_connection:
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
    global args
    args = parser.parse_args()


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

