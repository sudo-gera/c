import asyncio
import sys
import ipaddress
import common
import uuid
import typing
import io

stdin : asyncio.StreamReader
stdout : asyncio.StreamWriter

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

async def connect_stdin_stdout() -> tuple[asyncio.StreamReader, asyncio.StreamWriter]:
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    await loop.connect_read_pipe(lambda: protocol, sys.stdin)
    w_transport, w_protocol = await loop.connect_write_pipe(asyncio.streams.FlowControlMixin, sys.stdout)
    writer = asyncio.StreamWriter(w_transport, w_protocol, reader, loop)
    return reader, writer


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

async def sender() -> None:
    r : asyncio.StreamReader | None = None
    w : asyncio.StreamWriter | None = None
    try:
        while 1:
            await asyncio.sleep(0.01)
            if w is None:
                try:
                    r,w = await asyncio.open_connection('127.0.0.1', 2101)
                except ConnectionRefusedError:
                    continue
            assert w is not None
            for data in to_send:
                w.write(data+b'\x03')
            await w.drain()
            to_send.clear()
    finally:
        if w is not None:
            await common.safe_socket_close(w)


to_send : list[bytes] = []

async def main() -> None:
    fire(sender())
    global stdin, stdout
    stdin, stdout = await connect_stdin_stdout()
    buffer = b''
    continue_working = True
    chunks_buffer : list[bytes] = []
    stop_waiter = [0]
    while continue_working:
        try:
            data = await stdin.read(2**16)
        except BrokenPipeError as e:
            data = b'broken pipe, exiting...'
            continue_working = False
        if not data:
            data = b'no data, exiting...'
            continue_working = False
        buffer += data
        while b'\n' in buffer:
            data, buffer = buffer.split(b'\n', 1)
            if data.endswith(b'\r'):
                data = data[:-1]
            if b' \x00 ' in data:
                assert data.count(b' \x00 ') == 1
                # stdout.write(repr(data).encode()+b'\n')
                # await stdout.drain()
                data = b'\r'.join(data.split(b' \x00 ')[::-1])
                # stdout.write(repr(data).encode()+b'\n')
                # await stdout.drain()
            if b'\x05' not in data:
                chunks_buffer.append(data)
        # chunks_buffer = [b'\n'.join(chunks_buffer)]
        while chunks_buffer:
            # try:
            #     r,w = await asyncio.open_connection('127.0.0.1', 2101)
            # except ConnectionRefusedError:
            #     break
            # try:
            data = chunks_buffer[0]
            # stdout.write(repr(data).encode()+b'\n')
            # await stdout.drain()
            global prefix
            if b'\x03\x03\x03' in data:
                stop_waiter[0] |= 1
                async def stop_everything() -> None:
                    await asyncio.sleep(4)
                    try:
                        r_,w_ = await asyncio.open_connection('127.0.0.1', 2102)
                    except ConnectionRefusedError as e:
                        output = io.StringIO()
                        print(type(e), e, file=output)
                        output.seek(0)
                        stdout.write(output.read().encode())
                        await stdout.drain()
                    else:
                        await common.safe_socket_close(w_)
                    stop_waiter[0] |= 2
                fire(stop_everything())
            if b'\x02' in data:
                # stdout.write(repr(data).encode()+b'\n')
                # await stdout.drain()
                prefix = data.split(b'\x02', 1)[0]
            else:
                if b'\r' in data:
                    assert len(data.split(b'\r'))==2
                    data = data.split(b'\r')[0] + b'\r' + prefix + data.split(b'\r')[1] + clear_color.encode()
                else:
                    data = prefix + data + clear_color.encode()
                data += b'\n'
                # stdout.write(repr(data).encode()+b'\n')
                # await stdout.drain()
                to_send.append(data)
            chunks_buffer[:1] = []

    while stop_waiter[0] == 1:
        await asyncio.sleep(0.1)


if __name__ == '__main__':
    asyncio.run(main())

