import asyncio
import stream
import pickle

class udp_connection(asyncio.DatagramProtocol):
    def __init__(self, tcp_connection: stream.Stream) -> None:
        self.tcp_connection = tcp_connection
    
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = pickle.dumps((data, addr))
        self.tcp_connection.write(len(message).to_bytes(8, 'little'))
        self.tcp_connection.write(message)
        asyncio.create_task(self.tcp_connection.drain())

async def main():
    print("Starting UDP server")

    # Get a reference to the event loop as we plan to use
    # low-level APIs.
    loop = asyncio.get_running_loop()

    # One protocol instance will be created to serve all
    # client requests.

    try:
        async with stream.Stream(*await asyncio.open_connection('127.0.0.1', 64001)) as tcp_connection:
            transport, protocol = await loop.create_datagram_endpoint(lambda: udp_connection(tcp_connection), local_addr=('127.0.0.1', 60001))
            while 1:
                message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
                data, addr = pickle.loads(message)
                transport.sendto(data, addr)
    finally:
        transport.close()


asyncio.run(main())
