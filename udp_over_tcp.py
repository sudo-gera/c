import asyncio
from asyncio import transports
import inspect
import argparse
import ipaddress
import urllib.parse
import sys
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

class columned:
    def __init__(self, s):
        s = s.split(':')
        a = []
        while s:
            for q in range(len(s)):#, 0, -1):
                try:
                    d = '//'+':'.join(s[q:])
                    print(d)
                    f = urllib.parse.urlsplit(d)
                    f.hostname
                    f.port
                    a.append(f)
                    s[q:]=[]
                    break
                except Exception:
                    pass
        a = a[::-1]
        self.hosts = [q.hostname for q in a]
        self.ports = [q.port for q in a]

    def __repr__(self) -> str:
        return repr(list(zip(self.hosts, self.ports)))


async def main():
    parser = argparse.ArgumentParser()
    # parser.add_argument('--tcp', type=host_port, action='append')
    # parser.add_argument('--udp', type=host_port, action='append')
    # parser.add_argument('--udp', type=host_port)
    args = parser.parse_args()
    print(args)

# asyncio.run(main())
print(columned(sys.argv[1]))

