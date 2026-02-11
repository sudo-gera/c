from __future__ import annotations

import argparse
import asyncio

from aiohttp import web


parser = argparse.ArgumentParser()
parser.add_argument("--http-host", type=str, required=True)
parser.add_argument("--http-port", type=int, required=True)
parser.add_argument("--tcp-host",  type=str, required=True)
parser.add_argument("--tcp-port",  type=int, required=True)
args = parser.parse_args()

http_host = args.http_host
assert isinstance(http_host, str)
http_port = args.http_port
assert isinstance(http_port, int)
tcp_host = args.tcp_host
assert isinstance(tcp_host, str)
tcp_port = args.tcp_port
assert isinstance(tcp_port, int)

SESSIONS: dict[str, tuple[asyncio.StreamReader, asyncio.StreamWriter]] = {}

async def open_handler(request: web.Request) -> web.Response:
    sid = request.query["id"]

    reader, writer = await asyncio.open_connection(
        tcp_host, tcp_port
    )
    
    SESSIONS[sid] = reader, writer

    return web.Response(text='ok')

async def send_handler(request: web.Request) -> web.Response:
    sid = request.query["id"]
    reader, writer = SESSIONS[sid]

    data = await request.read()

    writer.write(data)

    if not data:
        writer.write_eof()

    await writer.drain()

    return web.Response(text='ok')

async def recv_handler(request: web.Request) -> web.Response:
    sid = request.query["id"]
    reader, writer = SESSIONS[sid]

    data = await reader.read(2**16)

    return web.Response(
        body=data,
        content_type="application/octet-stream",
    )

def main() -> None:
    app = web.Application()

    app.router.add_post("/open", open_handler)
    app.router.add_post("/send", send_handler)
    app.router.add_get("/recv", recv_handler)

    web.run_app(app, host=http_host, port=http_port)


if __name__ == "__main__":
    main()
