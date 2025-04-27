import asyncio
import sys
import ipaddress
import common
import uuid
import typing
import time

hosts = sys.argv[1:]
my_ip = common.select_my_ip(hosts)

hosts.sort()
clear_color = '\x1b[0m'

colors = [
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
    '\x1b[97m',
]
my_color = colors[hosts.index(my_ip)]

async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    ip = my_ip
    color = my_color
    try:
        while 1:
            data = (await reader.readline()).decode()
            if data.endswith('\n'):
                data = data[:-1]
            if not data:
                return
            for line in data.split('\n'):
                print(f'{color}[  {ip:12s}][ {time.strftime("%Y.%m.%d %H:%M:%S")}.{time.time_ns()//10**6%10**3:03d} ] ' + line + clear_color)
            # print('\n'.join([color + '[' + ip + '] ' + line + clear_color for line in data.split('\n')]))
    finally:
        await common.safe_socket_close(writer)
    
async def main() -> None:
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2102) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

