import asyncio
import sys
import ipaddress
import common
import uuid
import typing

log_server = sys.argv[1]
# hosts = sys.argv[2:]

# my_ip = common.select_my_ip(hosts)


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



async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        while 1:
            chunk = await reader.read(2**16)
            r, w = await asyncio.open_connection(log_server, 2101)
            try:
                w.write(chunk)
                await w.drain()
            finally:
                await common.safe_socket_close(w)
    finally:
        await common.safe_socket_close(writer)
    
async def main() -> None:
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2102) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

