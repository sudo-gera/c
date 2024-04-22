import asyncio
import pickle

import stream

class udp_connection:
    def __init__(self, tcp_connection, addr = None):
        self.addr = addr
        self.tcp_connection = tcp_connection

    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        if self.addr is not None:
            addr = self.addr
        message = pickle.dumps((data, addr))
        self.tcp_connection.write(len(message).to_bytes(8, 'little'))
        self.tcp_connection.write(message)
        asyncio.create_task(self.tcp_connection.drain())

