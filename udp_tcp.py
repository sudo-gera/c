import asyncio
import pickle

import stream


class udp_connection(asyncio.DatagramProtocol):
    def __init__(self, tcp_stream: stream.Stream, addr: tuple[str, int]|None = None) -> None:
        self.addr = addr
        self.tcp_stream = tcp_stream
    
    def connection_made(self, transport: object) -> None:
        assert isinstance(transport, asyncio.BaseTransport)
        self.transport = transport

    def datagram_received(self, data: bytes, addr: tuple[str, int]) -> None:
        if self.addr is not None:
            addr = self.addr
        print(19, data, addr)
        message = pickle.dumps((data, addr))
        self.tcp_stream.write(len(message).to_bytes(8, 'little'))
        self.tcp_stream.write(message)
        asyncio.create_task(self.tcp_stream.drain())

udp_clients : dict[tuple[str, int]|None, asyncio.BaseTransport]= {}

async def tcp_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter, is_client:bool=True) -> None:
    loop = asyncio.get_running_loop()

    data = None
    key = None
    addr = None
    async with stream.Stream(reader, writer) as tcp_stream:
        while 1:
            if key not in udp_clients and not (key is None and is_client):
                transport, protocol = await loop.create_datagram_endpoint(
                    lambda: udp_connection(tcp_stream, addr),
                    ('127.0.0.1', 60002) if not is_client else None,
                    ('127.0.0.1', 60002) if     is_client else None,
                )
                # assert isinstance(transport, asyncio.BaseTransport)
                udp_clients[key] = transport
            if data is not None:
                udp_clients[key].sendto(data, addr)
                data = None
            try:
                message = await tcp_stream.readexactly(int.from_bytes(await tcp_stream.readexactly(8), 'little'))
            except asyncio.IncompleteReadError:
                return
            data, addr = pickle.loads(message)
            print(50, data, addr)
            key = None
            if is_client:
                key, addr = addr, key

async def main(is_client) -> None:
    if is_client:
        ser = await asyncio.start_server(tcp_connection, '127.0.0.1', 64001)
        async with ser:
            await ser.serve_forever()
    else:
        loop = asyncio.get_running_loop()
        rw = await asyncio.open_connection('127.0.0.1', 64001)
        await tcp_connection(*rw, False)

