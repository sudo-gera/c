import ipaddress
import common
import asyncio
import sys
import time
import psutil
import traceback

hosts = sys.argv[1:]
my_ip = common.select_my_ip(hosts)
other_hosts = {*hosts} - {my_ip}

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        host = writer.get_extra_info('peername')
        print('got connection from', host)
    finally:
        await common.safe_socket_close(writer)

async def listening_server() -> None:
    try:
        async with await asyncio.start_server(on_connection, '0.0.0.0', 4444) as server:
            await server.serve_forever()
    except:
        print(traceback.format_exc())

async def ping_one_host(host:str) -> None:
    try:
        reader, writer = await common.run_with_timeout(asyncio.open_connection(host, 4444), 1)
        try:
            print('connected to', host)
        finally:
            await common.safe_socket_close(writer)
    except Exception:
        pass

async def pinger() -> None:
    while 1:
        await asyncio.sleep(1)
        await asyncio.gather(*map(ping_one_host, other_hosts))

async def main() -> None:
    asyncio.gather(
        pinger(),
        listening_server(),
    )

if __name__ == '__main__':
    asyncio.run(main())


