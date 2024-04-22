import asyncio
import pickle

import stream

udp_clients = {}

class udp_connection(asyncio.DatagramProtocol):
    def __init__(self, tcp_connection: stream.Stream, addr: tuple[str, int]|None = None) -> None:
        self.addr = addr
        self.tcp_connection = tcp_connection
    
    def connection_made(self, transport: asyncio.DatagramTransport):
        self.transport = transport

    def datagram_received(self, data, addr):
        if self.addr is not None:
            addr = self.addr
        message = pickle.dumps((data, addr))
        self.tcp_connection.write(len(message).to_bytes(8, 'little'))
        self.tcp_connection.write(message)
        asyncio.create_task(self.tcp_connection.drain())

async def tcp_connection(reader, writer, is_local=True):
    loop = asyncio.get_running_loop()

    async with stream.Stream(reader, writer) as tcp_connection:
        while 1:
            try:
                message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
            except asyncio.IncompleteReadError:
                return
            data, addr = pickle.loads(message)
            key = None
            if is_local:
                key, addr = addr, key
            if key not in udp_clients:
                transport, protocol = await loop.create_datagram_endpoint(
                    lambda: udp_connection(tcp_connection, addr),
                    remote_addr=('127.0.0.1', 60002)
                )
                udp_clients[key] = transport
            udp_clients[key].sendto(data, addr)
