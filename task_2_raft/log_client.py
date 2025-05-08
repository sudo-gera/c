import asyncio
import sys
import ipaddress
import common
import uuid
import typing

##############################################################################################################################################

tasks : set[asyncio.Task[None]] = set()

def fire(coro: typing.Awaitable[typing.Any]) -> None:
    async def wrapper() -> None:
        await coro
    task : asyncio.Task[None] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

##############################################################################################################################################
# log_server = sys.argv[1]
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

clear_color = '\x1b[0m'


# async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
#     try:
#         while 1:
#             chunk = await reader.read(2**16)
#             r, w = await asyncio.open_connection(log_server, 2101)
#             try:
#                 w.write(chunk)
#                 await w.drain()
#             finally:
#                 await common.safe_socket_close(w)
#     finally:
#         await common.safe_socket_close(writer)
    
# async def main() -> None:
#     async with await asyncio.start_server(log_handler, '0.0.0.0', 2102) as server:
#         await server.serve_forever()

prefix = b''

async def main() -> None:
    buffer = b''
    continue_working = True
    while continue_working:
        try:
            data = sys.stdin.buffer.readline()
        except BrokenPipeError as e:
            data = b'broken pipe, exiting...'
            continue_working = False
        if not data:
            data = b'no data, exiting...'
            continue_working = False
        buffer += data
        while b'\n' in buffer:
            try:
                r,w = await asyncio.open_connection('127.0.0.1', 2101)
            except ConnectionRefusedError:
                break
            data, buffer = buffer.split(b'\n', 1)
            global prefix
            if b'\x03' in data:
                async def stop_everything() -> None:
                    await asyncio.sleep(4)
                    try:
                        r,w = await asyncio.open_connection('127.0.0.1', 2102)
                    except ConnectionRefusedError:
                        pass
                    else:
                        await common.safe_socket_close(w)
                fire(stop_everything())
            if b'\x02' in data:
                prefix = data.split(b'\x02', 1)[0]
            else:
                data = prefix + data + clear_color.encode()
                data += b'\n'
                try:
                    w.write(data)
                    w.write_eof()
                    await w.drain()
                finally:
                    await common.safe_socket_close(w)


if __name__ == '__main__':
    asyncio.run(main())

