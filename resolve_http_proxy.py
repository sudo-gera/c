import asyncio
import aiohttp
import socket
# from aiohttp import web
from urllib.parse import urlparse

# UPSTREAM_PROXY_HOST = '127.0.0.1'  # <-- Replace with your proxy
# UPSTREAM_PROXY_PORT = 8080  # <-- Replace with proxy port

# async def resolve_domain(domain):
#     loop = asyncio.get_event_loop()
#     infos = await loop.getaddrinfo(domain, None, proto=socket.IPPROTO_TCP)
#     return infos[0][4][0]  # Return first resolved IP

# async def handle_http_request(request):
#     parsed = urlparse(str(request.url))
#     host = parsed.hostname
#     port = parsed.port or 80
#     path = parsed.path or "/"
#     if parsed.query:
#         path += "?" + parsed.query

#     resolved_ip = await resolve_domain(host)
#     rewritten_url = f"{parsed.scheme}://{resolved_ip}:{port}{path}"

#     headers = dict(request.headers)
#     headers["Host"] = host  # Keep original host for virtual hosting

#     async with aiohttp.ClientSession() as session:
#         proxy_url = f"http://{UPSTREAM_PROXY_HOST}:{UPSTREAM_PROXY_PORT}"
#         async with session.request(
#             method=request.method,
#             url=rewritten_url,
#             headers=headers,
#             data=await request.read(),
#             proxy=proxy_url,
#             allow_redirects=False,
#         ) as resp:
#             response_headers = [(k, v) for k, v in resp.headers.items()]
#             body = await resp.read()
#             return web.Response(status=resp.status, headers=response_headers, body=body)

# async def handle_connect(request):
#     try:
#         target_host, target_port = request.match_info['tail'].split(":")
#         target_port = int(target_port)

#         resolved_ip = await resolve_domain(target_host)

#         reader, writer = await asyncio.open_connection(UPSTREAM_PROXY_HOST, UPSTREAM_PROXY_PORT)

#         # Send CONNECT to upstream proxy
#         connect_str = f"CONNECT {resolved_ip}:{target_port} HTTP/1.1\r\nHost: {target_host}\r\n\r\n"
#         writer.write(connect_str.encode())
#         await writer.drain()

#         # Wait for upstream proxy response
#         response = await reader.readuntil(b"\r\n\r\n")
#         if b"200 Connection established" not in response:
#             return web.Response(status=502, text="Upstream proxy failed to establish tunnel")

#         # Connection established, upgrade to raw tunnel
#         resp = web.StreamResponse(status=200, reason="Connection Established")
#         await resp.prepare(request)

#         async def pipe(reader, writer):
#             try:
#                 while not reader.at_eof():
#                     data = await reader.read(4096)
#                     if not data:
#                         break
#                     writer.write(data)
#                     await writer.drain()
#             except Exception:
#                 pass
#             finally:
#                 writer.close()

#         client_reader = request.transport._stream_reader
#         client_writer = request.transport._stream_writer

#         await asyncio.gather(
#             pipe(reader, client_writer),
#             pipe(client_reader, writer),
#         )
#         return resp

#     except Exception as e:
#         return web.Response(status=500, text=f"CONNECT error: {e}")

# async def dispatch_request(request):
#     if request.method == "CONNECT":
#         return await handle_connect(request)
#     else:
#         return await handle_http_request(request)

# app = web.Application()
# app.router.add_route('*', '/{tail:.*}', dispatch_request)

# if __name__ == '__main__':
#     web.run_app(app, port=8888)


async def resolve_domain(domain):
    loop = asyncio.get_event_loop()
    infos = await loop.getaddrinfo(domain, None, proto=socket.IPPROTO_TCP)
    return infos[0][4][0]  # Return first resolved IP

#!/usr/bin/env python3
import asyncio
import argparse
import time

import stream
import forwarding_parser

class New:
    def __rlshift__(self, oth):
        self.left = oth
        self.work()
        return self
    def __lshift__(self, oth):
        self.right = oth
        self.work()
        return self
    def work(self):
        try:
            self.left
            self.right
        except AttributeError:
            return
        self.left.append(self.right)

new = New()

async def copy(reader: stream.Stream, writer: stream.Stream, _hex):
    while (data := await reader.read(2**16)):
        writer.write(data)
        await writer.drain()

@stream.streamify
async def connection(server_socket: stream.Stream):
    try:
        data = await server_socket.readuntil(b'\r\n\r\n')
        print(data)
        method, sp, other = data.split(maxsplit=2)
        print(method, sp, other)
        if method.lower() != b'connect':
            return
        host, port = sp.split(b':')
        host = (await resolve_domain(host)).encode()
        data = method + b' ' + host + b':' + port + b' ' + other
        print(data)
        async with stream.Stream(await asyncio.open_connection(*args.connect[0])) as client_socket:
            if args.connect is not None:
                await client_socket.safe_write(data)
                data = await client_socket.readuntil(b'\r\n\r\n')
                await server_socket.safe_write(data)
            print(data)
            await asyncio.gather(
                copy(client_socket, server_socket, 'none'),
                copy(server_socket, client_socket, 'none'),
            )
    except Exception as e:
        print(type(e), e)
        raise

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1))
    global args
    args = parser.parse_args()

    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

asyncio.run(main())

