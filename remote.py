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

q=DataQueue()

r=[]

async def read():
    e=await connect_stdin()
    with term:
        while 1:
            f=await e.read(1)
            q.put(f)

    # r.append(iter(receive_key_event_unsafe()))
    # while 1:
    #     next(r[1])


    # while 1:
        # for w in receive_key_event_unsafe():
            # f=await r.read(1)
            # q.put(f)

# read_lock=asyncio.Lock()

def start_read():
    if not r:
        r.append(asyncio.create_task(read()))

async def get(req):
    print(85)
    start_read()
    t=await q.get_wait()
    print(88,t)
    return web.Response(text=base64.b64encode(t).decode())

async def post(req):
    data=await req.read()
    t=[]
    for q in data.split():
        if q==b'^^^^':
            raise KeyboardInterrupt
        q=base64.b64decode(q)
        if len(q)==2:
            q=q[:-1]
        t.append(q)
    t=b''.join(t)
    run=term.__exit__()
    sys.stdout.buffer.write(t)
    sys.stdout.flush()
    if run:
        term.__enter__()
    return web.Response()

def stop(req):
    raise KeyboardInterrupt

app = web.Application()
app.add_routes([web.get('/', get),
                web.get('/stop', stop),
                web.post('/', post)])

if __name__ == '__main__':
    web.run_app(app,host=sys.argv[1], port=sys.argv[2])
