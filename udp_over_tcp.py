import asyncio
from asyncio import transports
import inspect
import argparse
import ipaddress
# class connection(asyncio.DatagramProtocol, asyncio.Protocol):
#     def __init__(self, channel):
#         self.__channel = channel

#     def connection_made(self, transport: asyncio.DatagramTransport | asyncio.Transport) -> None:
#         self.__transport = transport

#     def connection_lost(self, exc: Exception | None) -> None:
#         self.__channel.send(id(self), inspect.stack()[0][3])



#     def data_ (self, exc: Exception | None) -> None:
#         self.__channel.send(id(self), inspect.stack()[0][3])

# c = connection()
# c.

def channel(reader, writer):
    try:
        ...
    finally:
        writer.close()

class host_port:
    def __init__(self, hp: str):
        self.port = hp[len(hp) - hp[::-1].index(':'):]
        self.host = ipaddress.ip_address(hp[:len(hp) - len(self.port) - 1])

    def __repr__(se)

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=host_port)
    args = parser.parse_args()
    print(args)

asyncio.run(main())
