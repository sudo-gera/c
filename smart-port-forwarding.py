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
import signal
import os

logging.basicConfig(level=logging.DEBUG)

inet_status = 0
inet_checktime = time.time()

def stop():
    logging.debug(inspect.stack()[1][3])
    os.kill(os.getpid(), signal.SIGTERM)

def check_inet():
    global inet_status
    global inet_checktime
    # count = 3600
    while 1:
        # inet_status = os.system('ping -ot 4 google.com') == 0
        # inet_status = os.system('ping -ot 1 192.168.141.135') != 0
        # inet_status = bool(i have direct access)
        # inet_status = os.system('ping -ot 1 192.168.43.64 >/dev/null 2>/dev/null') != 0
        inet_status = True
        inet_checktime = time.time()
        # logging.debug([inet_checktime, inspect.stack()[0][3]])
        time.sleep(1)
        # count -= 1
        # if not count:
        #     exit()
    
threading.Thread(target=check_inet).start()

last_dict = {}
def get_remote(addr: tuple[str,int])->tuple[str,int]:
    if addr not in last_dict:
        last_dict[addr] = [0,0]
    last = last_dict[addr]
    # d = {
    #     1080 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
    #     3737 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
    #     3838 : (('127.0.0.1', 6666), ('192.168.49.1', 1080)),
    #     8080 : (('127.0.0.1', 7777), ('192.168.49.1', 8080)),
    #     # 8082 : (('127.0.0.1', 7777), ('192.168.49.1', 8080)),
    #     8082 : (('127.0.0.1', 8484), ('192.168.49.1', 8080)),
    # }
    # logging.debug([inet_checktime, inspect.stack()[0][3]])
    d = {
        1080 : (('127.0.0.1', 6666), ('127.0.0.1', 6666)),
        # 3737 : (('127.0.0.1', 6666), ('127.0.0.1', 1090)),
        # 3838 : (('127.0.0.1', 6666), ('127.0.0.1', 1090)),
        8080 : (('127.0.0.1', 7777), ('127.0.0.1', 7777)),
        8082 : (('127.0.0.1', 7777), ('127.0.0.1', 8484)),
        # 8082 : (('127.0.0.1', 7777), ('127.0.0.1', 7777)),
        # 1084 : (('127.0.0.1', 6666), ('127.0.0.1', 1484))
        # 1084 : (('127.0.0.1', 6666), ('127.0.0.1', 6666))
    }
    if time.time() - inet_checktime > 8:
        stop()
        # exit()
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

    def connection_made(self, transport:asyncio.Transport) -> None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.transport = transport
        # logging.debug(['pausing', id(self)])
        self.transport.pause_reading()
        # logging.debug(['paused', id(self)])
        asyncio.create_task(self.connect())

    def data_received(self, data: bytes) -> None:
        self.time = time.time()
        # logging.debug([type(self).__name__,inspect.stack()[0][3], id(self)])
        self.other.transport.write(data)

    def eof_received(self) -> bool | None:
        self.time = time.time()
        # logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.other.transport.write_eof()
    
    def connection_lost(self, exc: Exception | None) -> None:
        self.time = time.time()
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        if hasattr(self, 'other'):
            self.other.transport.close()
            del self.other

class ClientConnection(Connection):
    def __init__(self, other=None):
        super().__init__()
        self.other = other
        self.wait_connected = asyncio.Queue()

    async def connect(self):
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        self.transport.resume_reading()
        self.wait_connected.put_nowait(None)

class ServerConnection(Connection):
    def __init__(self, addr):
        super().__init__()
        self.addr = addr

    async def connect(self):
        logging.debug([type(self).__name__,inspect.stack()[0][3]])
        try:
            loop = asyncio.get_running_loop()
            remote = get_remote(self.addr)
            _, other = await loop.create_connection(lambda: ClientConnection(self), *remote)
            await other.wait_connected.get()
            self.other = other
            # logging.debug([id(self), 'other is set'])
            # logging.debug(['resuming', id(self)])
            self.transport.resume_reading()
            # logging.debug(['resumed', id(self)])
        except Exception:
            self.transport.write_eof()
            self.transport.close()

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
                    try:
                        con.transport.write_eof()
                        con.transport.close()
                    except Exception:
                        pass
        for con_ref in to_remove:
            con_refs.remove(con_ref)

async def main():
    for addr in sys.argv[1:]:
        asyncio.create_task(create_server(addr))
    await clear()

try:
    asyncio.run(main())
except Exception:
    stop()
