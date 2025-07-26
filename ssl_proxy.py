from h import *
import asyncio
import sys
import re
import ssl
from functools import *
from itertools import *
from operator import *
import aiohttp
import http.server
import io
import traceback

import stream
import timeout

def get_host_port(url, default_port=None):
    r = itemgetter(slice(None, None, -1))
    host, port = (r(list(map(r, r(url).split(b':', 1)))) + [default_port])[:2]
    return host, int(port)

async def copy(r: stream.Stream, w: stream.Stream, http=False):
    while (data:=await r.read(2**16)):
        ic(data)
        w.write(data)
        if w.transport.get_write_buffer_size() > 2**16:
            await w.drain()

async def on_ssl_connect(url: str, is_ssl: bool, reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    async with stream.Stream(reader, writer) as local_sock:
        host, port = get_host_port(url, 443)
        ssl_context = ssl._create_unverified_context()
        if not is_ssl:
            ssl_context = None
        async with stream.Stream(*await asyncio.open_connection(host, port, ssl=ssl_context)) as remote_sock:
            await asyncio.gather(copy(local_sock, remote_sock), copy(remote_sock, local_sock))

async def on_connect(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    async with stream.Stream(reader, writer) as local_sock:
        data = bytearray()
        while 1:
            new_data = await local_sock.read(1)
            data += new_data
            if not new_data or data.endswith(b'\r\n\r\n') or data.endswith(b'\n\n'):
                break
            if len(data) > 2**16:
                return
        ic(data)
        match =re.match(r'([^ ]*) ([^ ]*) (.*)'.encode(), data, re.S)
        if not match:
            return
        method, url, other = match.groups()
        ic(method, url, other)
        if method == b'CONNECT':
            local_sock.write(b'HTTP/1.1 200 Connection established\r\n\r\n')
            await local_sock.drain()
            try:
                data = await local_sock.readexactly(1)
            except asyncio.IncompleteReadError:
                return
            is_ssl = data[0]==0x16
            ic(method, url, is_ssl)
            ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
            ssl_context.load_cert_chain('/Users/gera/localhost+2.pem', '/Users/gera/localhost+2-key.pem')
            ssl_context.check_hostname = False
            if not is_ssl:
                ssl_context = None
            async with await asyncio.start_server(partial(on_ssl_connect, url, is_ssl), '127.0.0.1',ssl=ssl_context) as server:
                async with stream.Stream(*await asyncio.open_connection(*server.sockets[0].getsockname())) as remote_sock:
                    remote_sock.write(data)
                    await asyncio.gather(copy(local_sock, remote_sock), copy(remote_sock, local_sock))
        else:
            async with stream.Stream(*await asyncio.open_connection('127.0.0.1', 8899)) as remote_sock:
                remote_sock.write(data)
                await asyncio.gather(copy(local_sock, remote_sock), copy(remote_sock, local_sock))


async def main():
    async with await asyncio.start_server(on_connect, '0.0.0.0', 9999) as server:
        await server.serve_forever()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass


