import asyncio
import pickle

import stream

class udp_connection:
    def __init__(self, addr, tcp_connection):
        self.addr = addr
        self.tcp_connection = tcp_connection

    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = pickle.dumps((data, self.addr))
        self.tcp_connection.write(len(message).to_bytes(8, 'little'))
        self.tcp_connection.write(message)
        asyncio.create_task(self.tcp_connection.drain())

udp_clients = {}

async def tcp_connection(reader, writer):
    loop = asyncio.get_running_loop()
    async with stream.Stream(reader, writer) as tcp_connection:
        while 1:
            message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
            data, addr = pickle.loads(message)
            if addr not in udp_clients:
                transport, protocol = await loop.create_datagram_endpoint(
                    lambda: udp_connection(addr, tcp_connection),
                    remote_addr=('127.0.0.1', 60001)
                )
                udp_clients[addr] = transport
            udp_clients[addr].sendto(data)

async def main():
    asyncio.start_server(tcp_connection, '127.0.0.1', 64001)

    # Get a reference to the event loop as we plan to use
    # low-level APIs.
    loop = asyncio.get_running_loop()

    on_con_lost = loop.create_future()
    message = 'Hello World!'

    transport, protocol = await loop.create_connection(
        lambda: udp_connection(message, on_con_lost),
        '127.0.0.1', 8888)

    # Wait until the protocol signals that the connection
    # is lost and close the transport.
    try:
        await on_con_lost
    finally:
        transport.close()


asyncio.run(main())