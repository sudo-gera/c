from aiohttp import web
import aiohttp
import aiohttp.web
import asyncio
import base64
import sys
import termios
import copy
import time

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

d={}

async def get(req):
    data=b''
    try:
        name=req.match_info['name']
        if name not in d:
            d[name]=DataQueue()
        data=await d[name].get_wait()
    finally:
        return aiohttp.web.Response(body=data)

async def post(req):
    name=req.match_info['name']
    if name not in d:
        d[name]=DataQueue()
    d[name].put(req.read())
    return aiohttp.web.Response()

def start(req):
    name=str(time.time())
    print(f'python remote.py http://127.0.0.1:{sys.argv[2]}/{name}')
    return aiohttp.web.Response(text=
        f'''export REMOTE_URL='http://{req.host}/{name}'\n'''+
        open('remote.sh').read()
    )


app = web.Application()
app.add_routes([
    web.get('/', start),
    web.get('/{name}', get),
    web.post('/{name}', post)
])

if __name__ == '__main__':
    web.run_app(app,host=sys.argv[1], port=sys.argv[2])
