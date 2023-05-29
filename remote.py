import aiohttp
from aiohttp import web
import asyncio
import base64
import sys
import termios
import copy

class DataQueue:
    def __init__(self):
        self.queue=asyncio.Queue()
        self.len=0
        self.lock=asyncio.Lock()
    def put(self,val:bytes):
        assert type(val) in [bytes, bytearray]
        self.queue.put_nowait(val)
        self.len+=len(val)
    def get(self):
        data=[]
        try:
            while 1:
                chunk=self.queue.get_nowait()
                self.len-=len(chunk)
                data.append(chunk)
        except asyncio.QueueEmpty:
            pass
        data=b''.join(data)
        return data
    def __len__(self):
        return self.len
    async def get_wait(self):
        async with self.lock:
            data=await self.queue.get()
            self.len-=len(data)
            g=self.get()
            data+=g
            return data

class term_c:
    def __init__(self) -> None:
        self.entered=0
    def __enter__(self):
        print('enter')
        self.entered=1
        self.fd=sys.stdin.fileno()
        self.mode=termios.tcgetattr(self.fd)
        self.save=copy.copy(self.mode)
        self.mode[0] &= ~(termios.BRKINT | termios.ICRNL | termios.INPCK | termios.ISTRIP | termios.IXON)
        self.mode[1] &= ~(termios.OPOST)
        self.mode[2] &= ~(termios.CSIZE | termios.PARENB)
        self.mode[2] |= termios.CS8
        self.mode[3] &= ~(termios.ECHO | termios.ICANON | termios.IEXTEN | termios.ISIG)
        self.mode[6][termios.VMIN] = 1
        self.mode[6][termios.VTIME] = 0
        termios.tcsetattr(self.fd, termios.TCSAFLUSH, self.mode)
        return self
    def __exit__(self,*a,**s):
        print('exit')
        if self.entered:
            termios.tcsetattr(self.fd, termios.TCSADRAIN, self.save)
            self.entered=0
            return True

term=term_c()

async def connect_stdin():
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    await loop.connect_read_pipe(lambda: protocol, sys.stdin.buffer)
    return reader

async def read():
    e=connect_stdin()
    with term:
        async with aiohttp.ClientSession() as session:
            f=await e.read(1)
            async with session.post(sys.argv[1]+'_server',data=f) as resp:
                pass

async def write():
    async with aiohttp.ClientSession() as session:
        async with session.get(sys.argv[1]+'_client') as resp:
            f=await resp.read()
            run=term.__exit__()
            print(f)
            if run:
                term.__enter__()


async def main():
    asyncio.gather(
        read(),
        write()
    )
