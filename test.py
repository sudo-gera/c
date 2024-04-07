import asyncio
import ssl
import re

import stream
# from icecream import ic
from h import ic

# async def work(r, w):
#     while 1:
#         data = await r.read(2**16)
#         print('got data:', data)
#         w.write(data)
#         await w.drain()

# async def connection(r, w):
#     print('connection started')
#     async with stream.Stream(r, w) as s:
#         async with stream.Stream(*await asyncio.open_connection('venus.web.telegram.org', 443, ssl=True)) as web:
#             await asyncio.gather(work(s, web), work(web, s))
#     print('connection stopped')

# q1 = asyncio.Queue()
# q2 = asyncio.Queue()
# q2.put_nowait(None)

data_to_ssl = asyncio.Queue(maxsize=1)
owner = 0

async def server_copy(r, w):
    while 1:
        data = await r.read(2**16)
        # ic(data)
        if not data: break
        w.write(data)
        await w.drain()

async def server_connection(r, w):
    me = None
    async with stream.Stream(r, w) as local:
        try:
            data = await local.readuntil(b'\r\n\r\n')
        except asyncio.IncompleteReadError:
            return
        match = re.match(r'CONNECT ([^ ]+) '.encode(), data)
        if match is None:
            return
        remote_url = match.groups()[0]
from pprint import pprint
import mitmproxy
import mitmproxy.http
import json
import time
from traceback import *
import asyncio
import pickle
import base64
from serialize import *

class mitm:
    async def request(self, flow:mitmproxy.http.HTTPFlow):
        data=flow.request.path[1:]
        data=decode(data)
        name, req = loads(data,mitmproxy.http.Request)
        flow.request=req
        flow.name=name
    async def response(self, flow:mitmproxy.http.HTTPFlow):
        name, resp = flow.name, flow.response
        data=dumps([name, resp])
        data=encode(data)
        flow.response=flow.response.make(200,data)
    async def error(self, flow):
        print(time.asctime())
        print(time.time())
        print('error')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
        print()
        print()

addons = [mitm()]
        port, host = remote_url[::-1].split(b':',1)
        host, port = host[::-1], port[::-1]
        try:
            ic('trying to put data into the queue', data)
            await data_to_ssl.put((host, port))
            global owner
            owner += 1
            me = owner 
            ic('i am owner', me, data)
            local.write(b'HTTP/1.1 200 Connection established\r\n\r\n')
            await local.drain()
            async with stream.Stream(*await asyncio.open_connection('127.0.0.1', 2000)) as remote:
                await asyncio.gather(server_copy(local, remote), server_copy(remote, local))
        finally:
            ic('checking owner at exit', me, owner, data_to_ssl.qsize())
            if me == owner:
                if not data_to_ssl.empty():
                    data_to_ssl.get_nowait()
        

async def ssl_server_connection(r, w):
    async with stream.Stream(r, w) as local:
        host, port = data_to_ssl.get_nowait()
        ic('got', host, port)
        con = ssl._create_unverified_context()
        async with stream.Stream(*await asyncio.open_connection(host, port, ssl=con)) as remote:
            await asyncio.gather(server_copy(local, remote), server_copy(remote, local))

async def start_ssl_server():
    con = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    con.load_cert_chain(certfile='/Users/gera/localhost+2.pem', keyfile='/Users/gera/localhost+2-key.pem')
    server = await asyncio.start_server(ssl_server_connection, '0.0.0.0', 2000, ssl=con)
    async with server:
        await server.serve_forever()

async def start_server():
    server = await asyncio.start_server(server_connection, '0.0.0.0', 8080)
    async with server:
        await server.serve_forever()

async def main():
    await asyncio.gather(
        start_server(),
        start_ssl_server(),
    )

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass

