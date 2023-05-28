from __future__ import annotations
from h import *
import time

sys.argv=['-','4433:localhost:4433','http://...']

if len(sys.argv)==2:
    http_listen=('0.0.0.0:'+sys.argv[1]).split(':')[-2:]
    http_connect=None
    tcp_listen=None
    tcp_connect=None
elif len(sys.argv)==3:
    http_listen=None
    http_connect=sys.argv[2]
    tcp_connect=(':'+sys.argv[1]).split(':')[-4:]
    tcp_listen,tcp_connect=tcp_connect[:2],tcp_connect[2:]
else:
    print(f'''to start server: {sys.argv[0]} [http-listen-host:]http-listen-port''')
    print(f'''to start client: {sys.argv[0]} [tcp-listen-host:]tcp-listen-port:tcp-remote-host:tcp-remote-port http(s)://-started-url''')
    exit(1)

connections:dict[str,connection]={}
conn_lock=asyncio.Lock()

conn_time=6*3600
live_time=600

async def async_later(coro,time):
    await asyncio.sleep(time)
    await coro

def later(coro,time):
    asyncio.create_task(async_later(coro,time))    

def mem(q):
    self=0
    async def e(r):
        try:
            return await r
        except MemoryError:
            ic(traceback.format_exc())
            if self is not None:
                self.send_remove()
    @functools.wraps(q)
    def w(*a,**s):
        nonlocal self
        if a and type(a[0])==connection:
            self=a[0]
        elif a and type(a[0]) in [connection.h2t_c, connection.t2h_c]:
            self=a[0].conn
        else:
            self=None
        try:
            r=q(*a,**s)
            if asyncio.iscoroutine(r):
                return e(r)
            return r
        except MemoryError:
            ic(traceback.format_exc())
            if self is not None:
                self.send_remove()
    return w


class DataQueue:
    def __init__(self):
        self.queue=asyncio.Queue()
        self.len=0
        self.lock=asyncio.Lock()
    def put(self,val:bytes):
        ic(val)
        assert type(val) in [bytes, bytearray]
        self.queue.put_nowait(val)
        self.len+=len(val)
    def get(self):
        ic()
        data=[]
        ic()
        try:
            while 1:
                ic()
                chunk=self.queue.get_nowait()
                ic()
                self.len-=len(chunk)
                ic()
                data.append(chunk)
                ic()
        except asyncio.QueueEmpty:
            pass
        ic(data)
        data=b''.join(data)
        ic(data)
        return data
    def __len__(self):
        return self.len
    async def get_wait(self):
        ic()
        data=await self.queue.get()
        ic(data)
        # raise StopIteration
        g=self.get()
        ic(data,g,type(data),type(g))
        ic(data+g)
        data+=g
        ic(data)
        return data

events = DataQueue()

class connection(asyncio.Protocol):
    class t2h_c:
        def __init__(self,conn:connection):
            self.conn=conn
            self.loop=asyncio.create_task(self.session_loop())
            self.queue=DataQueue()
            self.num=0
        @mem
        async def session_loop(self):
            ic()
            if http_connect:
                ic()
                # async with aiohttp.ClientSession(trust_env=True) as session:
                if 1:
                    ic()
                    while self.conn.work:
                        ic()
                        data=await self.what_to_send()
                        ic(http_connect)
                        # async with session.post(f'''{http_connect}/{self.conn.name}/{':'.join(self.conn.forward_to)}''', data=data) as resp:
                            # pass
        @mem
        def update_reading(self):
            if len(self.queue)<4096000:
                self.conn.transport.resume_reading()
            else:
                self.conn.transport.pause_reading()
        @mem
        async def what_to_send(self):
            ic()
            data=await self.queue.get_wait()
            ic(data)
            self.update_reading()
            return data+events.get()
        @mem
        def event(self,ev,data=None):
            d=dict(
                type=ev,
                name=self.conn.name,
            )
            if ev!='new':
                num=self.num
                self.num+=1
                d['num']=num
            if ev=='got':
                d['data']=base64.b64encode(data).decode()
            ic(d)
            d=json.dumps(d)+'^'
            d=d.encode()
            if ev=='got':
                self.queue.put(d)
            else:
                events.put(d)
            if ev=='del':
                later(self.conn.async_local_remove(),4)
        @mem
        def remove(self):
            self.conn=None
            self.loop.cancel()

    class h2t_c:
        def __init__(self,conn):
            self.conn=conn
            self.loop=asyncio.create_task(self.session_loop())
            self.num=0
            self.buff=[]
        @mem
        async def session_loop(self):
            ic()
            if http_connect:
                ic()
                async with aiohttp.ClientSession(trust_env=True) as session:
                        ic()
                        while self.conn.work:
                            ic()
                            try:
                                ic(http_connect)
                                async with session.get(f'''{http_connect}/{self.conn.name}/{':'.join(self.conn.forward_to)}''') as resp:
                                    data=await resp.read()
                                    await self.received(data)
                            except asyncio.exceptions.TimeoutError:
                                pass
                            except aiohttp.client_exceptions.ServerDisconnectedError:
                                exit()
        @mem
        async def received(self,all_data):
            ic(all_data)
            for data in all_data.split('^')[:-1]:
                data=json.loads(data)
                conn=await get_connection(data['name'])
                if conn:
                    ic(conn.h2t,type(conn.h2t),conn.h2t.event,type(conn.h2t.event))
                    await conn.h2t.event(data)
        async def event(self,data):
            ic(data)
            if data['type']=='new':
                return
            self.buff.append((data['num'],data))
            self.buff.sort()
            for num,ev in self.buff:
                if num!=self.num:
                    break
                self.num+=1
                if ev['type']=='got':
                    self.conn.transport.write(base64.b64decode(ev['data']))
                if ev['type']=='eof':
                    self.conn.transport.write_eof()
                if ev['type']=='del':
                    self.conn.local_remove()
            if len(self.buff)>1024:
                self.conn.close()
        @mem
        def remove(self):
            self.conn=None
            self.loop.cancel()

    @mem
    def connection_made(self, transport: asyncio.Transport) -> None:
        self.transport=transport
        self.t2h.event('new')
    @mem
    def data_received(self, data: bytes) -> None:
        self.t2h.event('got',data)
    @mem
    def eof_received(self) -> None:
        self.t2h.event('eof')
    @mem
    def connection_lost(self, exc: Exception | None) -> None:
        self.t2h.event('del')
        

    def __init__(self,name=None,forward_to=None):
        ic()
        super().__init__()
        ic()
        if name is None:
            name=str(time.time())
        ic()
        if forward_to is None:
            forward_to=tcp_connect
        ic()
        connections[name]=self
        ic()
        self.forward_to=forward_to
        ic()
        self.name=name
        ic()
        self.work=1
        ic()
        self.t2h=self.t2h_c(self)
        ic()
        self.h2t=self.h2t_c(self)
        ic()

    async def connect(self):
        loop = asyncio.get_running_loop()
        await loop.create_connection(
            lambda: self,
            *self.forward_to.split(':'))
    
    def remove(self):
        self.connection_lost()
    
    def local_remove(self):
        self.work=0
        self.t2h.remove()
        self.h2t.remove()
        self.transport.close()
        if self.name in connections:
            connections[self.name]=None

    async def async_local_remove(self):
        self.local_remove()

#     def __init__(self,name=None,tcp_connect=tcp_connect):
#         super().__init__()
#         if name is None:
#             name=str(time.time())
#         connections[name]=self
#         self.lock=asyncio.Lock()
#         self.name=name
#         self.tcp_connect=tcp_connect
#         # self.h2t=asyncio.Queue()
#         # self.t2h=asyncio.Queue()
#         self.send_num=0
#         self.recv_num=0
#         self.work=1
#         self.dlen=0
#         # self.hlen=0
#         # self.tlen=0
#         self.recv_buff=[]
#         self.data_buff=b''
#         self.last=time.time()
#         self.poll=asyncio.create_task(self.recv())
#         self.push=asyncio.create_task(self.send())
#         self.dget=asyncio.create_task(self.enum_get())
#     @mem
#     async def connect(self):
#         loop = asyncio.get_running_loop()
#         await loop.create_connection(
#             lambda: self,
#             *self.tcp_connect.split(':'))
#     @mem
#     def update_reading(self):
#         if len(self.t2h)<4096:
#            self.transport.resume_reading()
#         else:
#             self.transport.pause_reading()
#     @mem
#     async def send_data(self):
#         data=self.t2h.get()
#         self.update_reading()
#         return data
#     @mem
#     async def recv(self):
#         if http_connect:
#             async with aiohttp.ClientSession(trust_env=True) as session:
#                     while self.work:
#                         try:
#                             async with session.get(f'''{http_connect}/{self.name}/{':'.join(self.tcp_connect)}''') as resp:
#                                 data=await resp.read()
#                                 self.recv_data(data)
#                         except asyncio.exceptions.TimeoutError:
#                             ic()
#                             pass
#                         except aiohttp.client_exceptions.ServerDisconnectedError:
#                             exit()
#     @mem
#     async def send(self):
#         if http_connect:
#             async with aiohttp.ClientSession(trust_env=True) as session:
#                 while self.work:
#                     data=await self.send_data()
#                     async with session.post(f'''{http_connect}/{self.name}/{':'.join(self.tcp_connect)}''', data=data) as resp:
#                         pass
#     @mem
#     def t2h_put(self,data):
#         self.last=time.time()
#         if 'data' in data:
#             data['data']=base64.b64encode(data['data']).decode()
#         data=json.dumps(data).encode()
#         self.t2h.put(data)
#         self.update_reading()
#     @mem
#     def later(self,d,t):
#         num=self.send_num
#         self.send_num=num+1
#         later(self.enum_put({
#             'connect': tcp_connect,
#             'num': num,
#         }|d),t)
#     @mem
#     def connection_made(self, transport: asyncio.Transport) -> None:
#         self.transport=transport
#         if http_connect:
#             self.later({
#                 'connect': tcp_connect,
#                 'event': 'new',
#             },1)
#     @mem
#     def data_received(self, data: bytes) -> None:self.later(({'event':'got','data':data,}),0)
#     @mem
#     def eof_received(self) -> None: self.later(({'event':'eof',}),4)
#     @mem
#     def connection_lost(self, exc: Exception | None) -> None:[self.later(({'event':'del',}),4),self.remove()]
#     @mem
#     async def enum_put(self, data: dict) -> None:
#         self.t2h_put(data)
#     @mem
#     async def async_remove(self):
#         self.transport.close()
#         self.work=0
#         async with conn_lock:
#             if self.name in connections:
#                 connections[self.name]=None
#         later(self.remove_later(),16)
#     @mem
#     def remove(self):
#         asyncio.create_task(self.async_remove())
#     @mem
#     def send_remove(self):
#         self.later(({
#             'event':'del',
#         }),4)
#         self.remove()
#     @mem
#     async def remove_later(self):
#         self.dget.cancel()
#         self.push.cancel()
#         self.poll.cancel()
#     @mem
#     def recv_data(self,data):
#         for d in data.split(b'^')[:-1]:
#             if d:
#                 self.h2t_put(d)
#             else:
#                 self.remove()
#     @mem
#     def h2t_put(self,data):
#         self.last=time.time()
#         l=len(data)
#         self.hlen+=l
#         data=data.decode()
#         data=json.loads(data)
#         if 'data' in data:
#             data['data']=base64.b64decode(data['data'])
#         data['l']=l
#         asyncio.create_task(self.async_put(self.h2t,data))
#     @mem
#     async def enum_get(self):
#         while self.work:
#             ev=await self.h2t.get()
#             self.hlen-=ev['l']
#             if ev['event']=='new':
#                 pass
#             else:
#                 num=ev['num']
#                 self.recv_buff.append((num,ev))
#                 self.recv_buff.sort()
#                 for num,ev in self.recv_buff:
#                     if num==self.recv_num:
#                         self.recv_num=num+1
#                         if ev['event']=='got':
#                             self.transport.write(ev['data'])
#                         if ev['event']=='eof':
#                             self.transport.write_eof()
#                         if ev['event']=='del':
#                             self.remove()
#                     else:
#                         break
#                 if len(self.recv_buff)>1024:
#                     self.send_remove()
#                 self.recv_buff=[(num,ev) for num,ev in self.recv_buff if num>=self.recv_num]

# def connections_len():
#     return len([w for q,w in connections.items() if w is not None])

async def get_connection(name,forward_to)->connection:
    ic()
    try:
        name=float(name)
    except:
        return None
    ic()
    t=time.time()
    ic()
    global connections
    ic()
    connections={q:w for q,w in connections.items() if w is not None or q+conn_time>t}
    ic()
    for name in connections:
        if connections[name] is not None:
            if connections[name].last+live_time<time.time():
                connections[name].remove()
    ic()
    if name in connections:
        return connections[name]
    ic()
    if time.time()>name+conn_time:
        return None
    ic()
    connections[name]=connection(name,forward_to)
    ic()
    await connections[name].connect()
    ic()
    return connections[name]


async def recv(req):
    name=req.match_info['name']
    forward_to=req.match_info['forward_to']
    ic(name,forward_to)
    conn=await get_connection(name,forward_to)
    ic(name,forward_to)
    if conn is None:
        return aiohttp.web.Response(text='')
    ic(name,forward_to)
    data=await req.read()
    ic(name,forward_to)
    conn.h2t.received(data)
    ic(name,forward_to)
    return aiohttp.web.Response(text=bin(len(data))[2:])

async def send(req):
    name=req.match_info['name']
    forward_to=req.match_info['forward_to']
    ic(name,forward_to)
    conn=await get_connection(name,forward_to)
    ic(name,forward_to)
    if conn is None:
        return aiohttp.web.Response(text='')
    ic(name,forward_to)
    data=await conn.t2h.what_to_send()
    ic(name,forward_to)
    return aiohttp.web.Response(body=data)

async def get_time(req):
    return aiohttp.web.Response(text=str(time.time()))

if http_listen:
    app = aiohttp.web.Application()
    app.add_routes([
        aiohttp.web.get('/', get_time),
        aiohttp.web.post('/{name}/{forward_to}', recv),
        aiohttp.web.get('/{name}/{forward_to}', send),
    ])
    aiohttp.web.run_app(app, host=http_listen[0], port=http_listen[1])
if http_connect:
    # http_client_name=urllib.request.urlopen(http_connect).read()
    async def main():
        loop = asyncio.get_running_loop()
        server = await loop.create_server(
            connection,
            *tcp_listen)
        async with server:
            await server.serve_forever()
        await asyncio.gather(*asyncio.all_tasks() - {asyncio.current_task()})
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
