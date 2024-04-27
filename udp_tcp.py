import asyncio
# import pickle
import json
import base64

import stream

send_queue = asyncio.Queue()

# async def sender(tcp_connection: stream.Stream):
#     while 1:
#         for chunk in range(16):
#             data = await send_queue.get()
#             tcp_connection.write(data)
#         await tcp_connection.drain()  
#         tcp_connection.transport.get_write_buffer_size()

class udp_connection(asyncio.DatagramProtocol):
    def __init__(self, tcp_connection: stream.Stream, addr: tuple[str, int]|None = None) -> None:
        self.addr = addr
        self.tcp_connection = tcp_connection
    
    def connection_made(self, transport: asyncio.DatagramTransport):
        self.transport = transport

    def datagram_received(self, data, addr):
        if self.addr is not None:
            addr = self.addr
        data = base64.b64encode(data).decode()
        message = json.dumps([data, list(addr)]).encode()
        message = len(message).to_bytes(8, 'little') + message
        if self.tcp_connection.transport.get_write_buffer_size() < 2**16:
            self.tcp_connection.write(message)

        # if send_queue.qsize() < 16:
        #     send_queue.put_nowait(message)

async def read_data(tcp_connection: stream.Stream):
    try:
        message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
    except asyncio.IncompleteReadError:
        return None, None
    data, addr = json.loads(message)
    addr = tuple(addr)
    data = base64.b64decode(data)
    return addr, data
