from __future__ import annotations
import asyncio
from asyncio import transports
import sys
import functools
import time
import urllib.request
import os
import logging
import inspect
import threading
import weakref
import traceback

logging.basicConfig(level=logging.DEBUG)

inet_status = 0

def check_inet():
    global inet_status
    while 1:
        inet_status = os.system('ping -ot 4 google.com') == 0
        time.sleep(1)
    
threading.Thread(target=check_inet).start()

last_dict = {}
def get_remote(addr: tuple[str,int])->tuple[str,int]:
    if addr not in last_dict:
        last_dict[addr] = [0,0]
    last = last_dict[addr]
    d = {
        1080 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
        3737 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
        3838 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
        8080 : (('127.0.0.1', 7777), ('192.168.49.1', 8080)),
        8082 : (('127.0.0.1', 7777), ('192.168.49.1', 8080)),
    }
    if inet_status:
        last[1] = d[addr[1]][0]
    else:
        last[1] = d[addr[1]][1]
    logging.debug([addr,last[1]])
    return last[1]

con_refs:set[weakref.ReferenceType[Connection]] = set()

class Connection(asyncio.Protocol):
    def __init__(self) -> None:
        super().__init__()
        self.time = time.time()
        con_refs.add(weakref.ref(self))

    def connection_made(self, transport) -> None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.transport = transport
        self.transport.pause_reading()
        asyncio.create_task(self.connect())

    def data_received(self, data: bytes) -> None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.write(data)

    def eof_received(self) -> bool | None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.write_eof()
    
    def connection_lost(self, exc: Exception | None) -> None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.close()
        del self.other

class ClientConnection(Connection):
    def __init__(self, other=None):
        super().__init__()
        self.other = other

    async def connect(self):
        self.transport.resume_reading()

class ServerConnection(Connection):
    def __init__(self, addr):
        super().__init__()
        self.addr = addr

    async def connect(self):
        loop = asyncio.get_running_loop()
        remote = get_remote(self.addr)
        _, other = await loop.create_connection(lambda: ClientConnection(self), *remote)
        self.other = other
        self.transport.resume_reading()

async def create_server(addr):
    addr=addr.split(':')
    addr[1]=int(addr[1])
    addr = tuple(addr)
    loop = asyncio.get_running_loop()
    server = await loop.create_server(lambda: ServerConnection(addr), *addr)
    async with server:
        await server.serve_forever()

async def clear():
    while 1:
        await asyncio.sleep(64)
        to_remove = set()
        for con_ref in con_refs:
            con = con_ref()
            if con is None:
                to_remove.add(con_ref)
            else:
                if time.time() - con.time > 128:
                    con.transport.write_eof()
                    con.transport.close()
        for con_ref in to_remove:
            con_refs.remove(con_ref)

        

async def main():
    for addr in sys.argv[1:]:
        asyncio.create_task(create_server(addr))
    await clear()

try:
    asyncio.run(main())
except Exception:
    print(traceback.format_exc())
    exit()
