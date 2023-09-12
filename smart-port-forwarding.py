import asyncio
from asyncio import transports
import sys
import functools
import time
import urllib.request
import os
import logging
import inspect
logging.basicConfig(level=logging.DEBUG)



# listen = [sys.argv[1], sys.argv[2]]


last_dict = {}
def get_remote(addr: tuple[str,int])->tuple[str,int]:
    if addr not in last_dict:
        last_dict[addr] = [0,0]
    last = last_dict[addr]
    if addr[1] in [1080,3737,3838]:
        if time.time() - last[0] > 60:
            if os.system('ping -ot 1 google.com > /dev/null') == 0:
                last[1] = ('127.0.0.1',6666)
            else:
                last[1] = ('192.168.49.1',1080)
    else:
        if time.time() - last[0] > 60:
            if os.system('ping -ot 1 google.com > /dev/null') == 0:
                last[1] = ('127.0.0.1',7777)
            else:
                last[1] = ('192.168.49.1',8080)
    logging.debug([addr,last[1]])
    return last[1]


class Connection(asyncio.Protocol):
    def connection_made(self, transport) -> None:
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.transport = transport
        self.transport.pause_reading()
        asyncio.create_task(self.connect())

    def data_received(self, data: bytes) -> None:
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.write(data)

    def eof_received(self) -> bool | None:
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.write_eof()
    
    def connection_lost(self, exc: Exception | None) -> None:
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.close()

class ClientConnection(Connection):
    def __init__(self, other=None):
        self.other = other
        super().__init__()

    async def connect(self):
        self.transport.resume_reading()

class ServerConnection(Connection):
    def __init__(self, addr):
        self.addr = addr
        super().__init__()

    async def connect(self):
        loop = asyncio.get_running_loop()
        remote = get_remote(self.addr)
        _, other = await loop.create_connection(lambda: ClientConnection(self), *remote)
        self.other = other
        self.transport.resume_reading()

async def main(addr=None):
    if addr is None:
        for addr in sys.argv[1:]:
            asyncio.create_task(main(addr))
        while 1:
            await asyncio.sleep(1)
    else:
        addr=addr.split(':')
        addr[1]=int(addr[1])
        addr = tuple(addr)
        loop = asyncio.get_running_loop()
        server = await loop.create_server(lambda: ServerConnection(addr), *addr)
        async with server:
            await server.serve_forever()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
