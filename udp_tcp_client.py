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
        print(15, data, self.addr)
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
            print(29, data, addr)
            if addr not in udp_clients:
                transport, protocol = await loop.create_datagram_endpoint(
                    lambda: udp_connection(addr, tcp_connection),
                    remote_addr=('127.0.0.1', 60001)
                )
                udp_clients[addr] = transport
            udp_clients[addr].sendto(data)

async def main():
    ser = await asyncio.start_server(tcp_connection, '127.0.0.1', 64001)
    async with ser:
        await ser.serve_forever()


asyncio.run(main())