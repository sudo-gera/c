import asyncio
import sys
import ipaddress
import common
import uuid
import typing

network = ipaddress.ip_network(sys.argv[1])

hosts : list[str] = []

async def try_host(host: str, on_success: typing.Callable[[str], None]):
    reader, writer = await asyncio.open_connection(host, 2100)
    try:
        token = uuid.uuid4().bytes.hex().encode()
        writer.write(b'echo '+token)
        writer.write_eof()
        await writer.drain()
        data = await reader.read()
        if data.strip() == token:
            on_success(host)
    except Exception:
        pass
    finally:
        await common.safe_socket_close(writer)

async def setup_network_changer():
    await asyncio.sleep(2)
    for host in network:
        asyncio.create_task(
            try_host(
                host, hosts.append
            )
        )
    while 1:
        await asyncio.sleep(2)
        await create_network_config()
    

async def create_network_config():
    ...


'''
*filter
:INPUT ACCEPT [7:488]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [4:424]
-I INPUT -p tcp --dport 4444 -j DROP
-I OUTPUT -p tcp --sport 4444 -j DROP
COMMIT
'''

colors = [
    '\x1b[0m',
    '\x1b[37m',
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
]

async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    data = await reader.read()
    host = data.split()[0]
    color = ''
    if host in hosts:
        color = colors[hosts.index(host)]
    

async def main():
    asyncio.create_task(setup_network_changer())
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2100) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

