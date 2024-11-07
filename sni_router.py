#!/usr/bin/env python3
import asyncio
import argparse
import time
import re

args = argparse.Namespace()

import stream
import forwarding_parser

vpn_hosts : list[str] = ['']

async def select_proxy_by_hostname(hostname: str) -> tuple[str, int]:
    for host in vpn_hosts:
        if re.fullmatch(host, hostname):
            return ('127.0.0.1', 8080)
    return ('127.0.0.1', 3128)

async def copy(reader: stream.Stream, writer: stream.Stream) -> None:
    while (data := await reader.read(2**16)):
        writer.write(data)
        await writer.drain()

@stream.streamify
async def connection(server_socket: stream.Stream) -> None:
    proxy_req = await server_socket.readuntil(b'\r\n\r\n')
    if proxy_req.lower().startswith(b'connect '):
        server_socket.write(b'HTTP/1.1 200 Connection established\r\n\r\n')
        await server_socket.drain()
        async with stream.Stream(await asyncio.open_connection(*args.sni_parser[0])) as client_socket:
            sni_req = await server_socket.read(2**16)
            client_socket.write(sni_req)
            await client_socket.drain()
            hostname_b = await client_socket.read()
            try:
                hostname = hostname_b.decode()
            except Exception:
                pass
        async with stream.Stream(await asyncio.open_connection(*await select_proxy_by_hostname(hostname))) as client_socket:
            client_socket.write(proxy_req)
            await client_socket.drain()
            await client_socket.readuntil(b'\r\n\r\n')
            client_socket.write(sni_req)
            await client_socket.drain()
            await asyncio.gather(
                copy(client_socket, server_socket),
                copy(server_socket, client_socket),
            )
    else:
        async with stream.Stream(await asyncio.open_connection(*args.default_proxy[0])) as client_socket:
            await asyncio.gather(
                copy(client_socket, server_socket),
                copy(server_socket, client_socket),
            )

async def main() -> None:
    from sys import stdin
    global vpn_hosts
    vpn_hosts = stdin.read().splitlines()
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--default-proxy', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--sni-parser', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    global args
    args = parser.parse_args()

    async with await asyncio.start_server(connection, *args.listen[0]) as server:
        await server.serve_forever()

asyncio.run(main())
