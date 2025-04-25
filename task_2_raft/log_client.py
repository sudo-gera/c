import asyncio
import sys
import ipaddress
import common
import uuid
import typing

hosts = sys.argv[1:]

my_ip = common.get_my_ip()


# colors = [
#     '\x1b[0m',
#     '\x1b[37m',
#     '\x1b[90m',
#     '\x1b[91m',
#     '\x1b[92m',
#     '\x1b[93m',
#     '\x1b[94m',
#     '\x1b[95m',
#     '\x1b[96m',
# ]



async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        while 1:
            chunk = await reader.read(2**16)
            r, w = await asyncio.open_connection(hosts[-1], 2101)
            try:
                w.write(my_ip.encode() + b' ' + chunk)
                await w.drain()
            finally:
                common.safe_close_socket(w)
    finally:
        common.safe_close_socket(writer)
    
async def main():
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2102) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

