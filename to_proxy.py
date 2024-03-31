import asyncio
import argparse
from functools import partial
import traceback
import re

async def copy_stream(r_q, w_q, inject):
    reader = await r_q.get()
    writer = await w_q.get()
    try:
        assert reader is not None
        assert writer is not None
        while 1:
            if inject is not None:
                data = await reader.readuntil()
                data = re.sub(b'([a-zA-Z]+ )', b'\\g<0>'+inject, data, 1)
                inject = None
            else:
                data = await reader.read(2**16)
            if not data: break
            writer.write(data)
            await writer.drain()
    except KeyboardInterrupt:
        pass
    finally:
        if writer is not None:
            writer.close()
            await writer.wait_closed()
        

async def connection(host, port, inject, a_reader, a_writer):
    c_w_q = asyncio.Queue()
    c_r_q = asyncio.Queue()
    a_w_q = asyncio.Queue()
    a_r_q = asyncio.Queue()
    a_r_q.put_nowait(a_reader)
    a_w_q.put_nowait(a_writer)
    asyncio.create_task(copy_stream(a_r_q, c_w_q, inject))
    asyncio.create_task(copy_stream(c_r_q, a_w_q, None))
    try:
        c_reader, c_writer = await asyncio.open_connection(host, port)
    except Exception:
        print(traceback.format_exc())
        c_r_q.put_nowait(None)
        c_w_q.put_nowait(None)
    else:
        c_r_q.put_nowait(c_reader)
        c_w_q.put_nowait(c_writer)

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen-host', type=str, required=True)
    parser.add_argument('--listen-port', type=int, required=True)
    parser.add_argument('--connect-host', type=str, required=True)
    parser.add_argument('--connect-port', type=int, required=True)
    parser.add_argument('--http-inject', type=str, required=True)
    args = parser.parse_args()

    server = await asyncio.start_server(partial(connection, args.connect_host, args.connect_port, args.http_inject), args.listen_host, args.listen_port)

    async with server:
        await server.serve_forever()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
