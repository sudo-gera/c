#!/usr/bin/env python3
import asyncio
import argparse
import asyncio.base_tasks
import time
import typing

import stream
import forwarding_parser
import asyncio

args = argparse.Namespace()

class UDPConnection(asyncio.DatagramProtocol):

    def connection_made(self, transport: asyncio.BaseTransport) -> None:
        self.transport = typing.cast(asyncio.DatagramTransport, transport)

    async def async_datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        message = len(data).to_bytes(2, 'big') + data
        async with stream.Stream(asyncio.open_connection(*args.connect[0])) as tcp_connection:
            await tcp_connection.safe_write(message)
            data_len = int.from_bytes(await tcp_connection.readexactly(2), 'big')
            data = await tcp_connection.readexactly(data_len)
        self.transport.sendto(data, addr)

    def datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        asyncio.create_task(self.async_datagram_received(data, addr))

async def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1))
    global args
    args = parser.parse_args()


    endpoint, _ = await asyncio.get_running_loop().create_datagram_endpoint(
        UDPConnection,
        args.listen[0],
    )

    try:
        await asyncio.Future()
    finally:
        endpoint.close()

if __name__ == '__main__':
    asyncio.run(main())

