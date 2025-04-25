import asyncio
import sys
import ipaddress
import common
import uuid
import typing

clear_color = '\x1b[0m',

colors = [
    '\x1b[37m',
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
]

host_to_color = {}

def color_by_host(ip: str):
    if ip not in host_to_color:
        host_to_color[ip] = colors[len(host_to_color)]
    return host_to_color[ip]

async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    data = (await reader.read()).decode()
    ip = data.split()[0]
    data = data[(len(data.split()[0]) + 1):]
    color = color_by_host(ip)
    print(color + data + clear_color)

async def main():
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2101) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

