import asyncio
import sys
import ipaddress
import common
import uuid
import typing

# clear_color = '\x1b[0m'

# colors = [
#     '\x1b[90m',
#     '\x1b[91m',
#     '\x1b[92m',
#     '\x1b[93m',
#     '\x1b[94m',
#     '\x1b[95m',
#     '\x1b[96m',
#     '\x1b[97m',
# ]

# host_to_color : dict[str, str] = {}

# def color_by_host(ip: str) -> str:
#     if ip not in host_to_color:
#         host_to_color[ip] = colors[len(host_to_color)]
#     return host_to_color[ip]

# async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
#     peername = writer.transport.get_extra_info('peername')
#     data = (await reader.read()).decode()
#     if data.endswith('\n'):
#         data = data[:-1]
#     if not data:
#         return
#     ip = peername[0]
#     # ip = data.split()[0]
#     # data = data[(len(data.split()[0]) + 1):]
#     color = color_by_host(ip)
#     print('\n'.join([color + '[' + ip + '] ' + line + clear_color for line in data.split('\n')]))

exit_queue : asyncio.Queue[None] = asyncio.Queue()

async def wait_for_exit() -> None:
    await exit_queue.get()
    exit_queue.put_nowait(None)
    raise TabError

async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    data = await reader.read()
    if data.startswith(b'GET'):
        exit_queue.put_nowait(None)
    else:
        sys.stdout.buffer.write(data)
        sys.stdout.buffer.flush()
    # sys.stdout.flush()
    # peername = writer.transport.get_extra_info('peername')
    # data = (await reader.read()).decode()
    # if data.endswith('\n'):
    #     data = data[:-1]
    # if not data:
    #     return
    # ip = peername[0]
    # # ip = data.split()[0]
    # # data = data[(len(data.split()[0]) + 1):]
    # color = color_by_host(ip)
    # print('\n'.join([color + '[' + ip + '] ' + line + clear_color for line in data.split('\n')]))

async def main() -> None:
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2101) as server:
        try:
            await asyncio.gather(
                wait_for_exit(),
                server.serve_forever(),
            )
        except TabError:
            pass

if __name__ == '__main__':
    asyncio.run(main())

