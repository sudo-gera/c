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

def receive_key_event_unsafe():
    # if you will use it in while(1)
    # you will never stop
    # ctrl+C returns as 3
    fd=sys.stdin.fileno()
    mode=termios.tcgetattr(fd)
    save=copy.copy(mode)
    mode[0] &= ~(termios.BRKINT | termios.ICRNL | termios.INPCK | termios.ISTRIP | termios.IXON)
    mode[1] &= ~(termios.OPOST)
    mode[2] &= ~(termios.CSIZE | termios.PARENB)
    mode[2] |= termios.CS8
    mode[3] &= ~(termios.ECHO | termios.ICANON | termios.IEXTEN | termios.ISIG)
    mode[6][termios.VMIN] = 1
    mode[6][termios.VTIME] = 0
    termios.tcsetattr(fd, termios.TCSAFLUSH, mode)
    try:
        yield
        # c=sys.stdin.buffer.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, save)

async def connect_stdin():
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    await loop.connect_read_pipe(lambda: protocol, sys.stdin.buffer)
    return reader

q=DataQueue()

r=[]

async def read():
    r=await connect_stdin()
    while 1:
        for w in receive_key_event_unsafe():
            f=await r.read(1)
            q.put(f)

read_lock=asyncio.Lock()

async def start_read():
    async with read_lock:
        if not r:
            r.append(asyncio.create_task(read()))

async def get(req):
    await start_read()
    t=await q.get_wait()
    return web.Response(text=base64.b64encode(t).decode())

async def post(req):
    data=await req.read()
    for q in data.split():
        print(q)
        if q==b'^^^^':
            raise KeyboardInterrupt
        q=base64.b64decode(q)
        if len(q)==2:
            q=q[:-1]
        sys.stdout.buffer.write(q)
    sys.stdout.flush()
    return web.Response()

def stop(req):
    raise KeyboardInterrupt

app = web.Application()
app.add_routes([web.get('/', get),
                web.get('/stop', stop),
                web.post('/', post)])

if __name__ == '__main__':
    web.run_app(app,host=sys.argv[1], port=sys.argv[2])
