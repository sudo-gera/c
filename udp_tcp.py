import asyncio
import pickle

import stream


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

