import asyncio
import sys
import ipaddress
import common
import uuid
import typing
import time


##############################################################################################################################################

tasks : set[asyncio.Task[None]] = set()

def fire(coro: typing.Awaitable[typing.Any]) -> None:
    async def wrapper() -> None:
        await coro
    task : asyncio.Task[None] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

##############################################################################################################################################

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

lock = asyncio.Lock()

stdin : asyncio.StreamReader
stdout : asyncio.StreamWriter

async def connect_stdin_stdout() -> tuple[asyncio.StreamReader, asyncio.StreamWriter]:
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    # await loop.connect_read_pipe(lambda: protocol, sys.stdin)
    w_transport, w_protocol = await loop.connect_write_pipe(asyncio.streams.FlowControlMixin, sys.stdout)
    writer = asyncio.StreamWriter(w_transport, w_protocol, reader, loop)
    return reader, writer

to_print : list[tuple[bytes, bytes]] = []

async def printer() -> None:
    global to_print
    t = f'{time.time_ns():024d}'.encode()
    await asyncio.sleep(0.1)
    while 1:
        old_t = t
        t = f'{time.time_ns():024d}'.encode()
        await asyncio.sleep(0.1)
        tpo = to_print[:0]
        tpn = to_print[:0]
        for data_time in to_print:
            if data_time[0] < t or data_time[1] < old_t:
                tpo.append(data_time)
            else:
                tpn.append(data_time)
        tp = [data for data, time in tpo]
        to_print = tpn
        tpe = [*enumerate(tp)]

        # stdout.write(str([tpe]).encode()+b'\n\n\n\n')
        # await stdout.drain()
        tpe.sort(key=lambda x:(x[1].split(b'\r',1)[0] if b'\r' in x[1] else b'', x[0]))
        # stdout.write(str([tpe]).encode()+b'\n\n\n\n')
        # await stdout.drain()

        tp = [data[1] for data in tpe]
        # tpb = b''.join(tp)
        async with lock:
            for data in tp:
                stdout.write(data.split(b'\r')[-1])
                # stdout.write(repr(data).encode()+b'==\n')
            # stdout.write(tpb)
            # stdout.write(str([tpb]).encode()+b'\n\n\n\n')
            await stdout.drain()


async def put_data(data: bytes) -> None:
    if data.startswith(b'GET'):
        exit_queue.put_nowait(None)
    else:
        # stdout.write(str(data).encode()+b'\n')
        # await stdout.drain()
        to_print.append((data, f'{time.time_ns():024d}'.encode()))

async def print_data(data: bytes) -> None:
    if data.startswith(b'GET'):
        exit_queue.put_nowait(None)
    else:
        stdout.write(data)
        await stdout.drain()
        # sys.stdout.buffer.write(data)
        # sys.stdout.buffer.flush()

async def data_handler(data: bytes) -> None:
    # if data.startswith(b'\x00'):
    #     if not lock.locked():
    #         await lock.acquire()
    #     await print_data(data)
    #     if b'\01' in data:
    #         lock.release()
    # else:
        # await print_data(data)
        await put_data(data)

async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    # print('new connection')
    buffer = b''
    first_msg = True
    try:
        while (data := await reader.read(2*16)):
            if data.upper().startswith(b'GET') and first_msg:
                exit_queue.put_nowait(None)
                # print('got GET')
                return
            else:
                first_msg = False
            buffer += data
            while b'\x03' in buffer:
                data, buffer = buffer.split(b'\x03', 1)
                fire(data_handler(data))
        # print('got EOF')
    finally:
        # print('closing connection')
        await common.safe_socket_close(writer)

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
    asyncio.create_task(printer())
    global stdin, stdout
    stdin, stdout = await connect_stdin_stdout()
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

