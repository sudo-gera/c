import asyncio
import argparse
from functools import partial
import traceback
import re
import json

async def copy_stream(r_q, w_q, inject, c_a_q):
    reader = await r_q.get()
    writer = None
    try:
        assert reader is not None
        # assert writer is not None
        while 1:
            if inject is not None:
                if inject == '-':
                    data = await reader.readuntil()
                    print(data)
                    c_a_q.put_nowait(json.loads(data))
                    data=b''
                    print(c_a_q.qsize(), id(c_a_q))
                else:
                    data = re.sub(b'([a-zA-Z]+ )', b'\\g<0>'+inject, data, 1)
                    inject = None
            else:
                data = await reader.read(2**16)
            if not data: break
            if writer is None:
                print(27)
                writer = await w_q.get()    
                print(29)
            writer.write(data)
            await writer.drain()
    except (KeyboardInterrupt, ConnectionResetError):
        pass
    finally:
        if writer is not None:
            writer.close()
            try:
                await writer.wait_closed()
            except ConnectionResetError:
                pass
        

async def connection(host, port, inject, connect, a_reader, a_writer):
    print(40, host, port, inject, connect)
    c_w_q = asyncio.Queue()
    c_r_q = asyncio.Queue()
    a_w_q = asyncio.Queue()
    a_r_q = asyncio.Queue()
    c_a_q = asyncio.Queue()
    a_r_q.put_nowait(a_reader)
    a_w_q.put_nowait(a_writer)
    asyncio.create_task(copy_stream(a_r_q, c_w_q, inject, c_a_q))
    asyncio.create_task(copy_stream(c_r_q, a_w_q, None, None))
    if inject == '-':
        connect = await c_a_q.get()
    try:
        c_reader, c_writer = await asyncio.open_connection(host, port)
    except Exception:
        print(traceback.format_exc())
        c_r_q.put_nowait(None)
        c_w_q.put_nowait(None)
    else:
        if connect:
            c_writer.write(f'''
CONNECT {connect} HTTP/1.1
Host: {connect}
User-Agent: curl/8.4.0
Proxy-Connection: Keep-Alive


'''[1:-1].replace('\n','\r\n').encode())
            await c_writer.drain()
            res = await c_reader.readuntil(b'\r\n\r\n')
            if res != b'HTTP/1.1 200 Connection established\r\n\r\n':
                print(res)
        c_r_q.put_nowait(c_reader)
        c_w_q.put_nowait(c_writer)

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen-host', type=str, required=True)
    parser.add_argument('--listen-port', type=int, required=True)
    parser.add_argument('--connect-host', type=str, required=True)
    parser.add_argument('--connect-port', type=int, required=True)
    parser.add_argument('--http-inject', type=str)
    parser.add_argument('--http-connect', type=str)
    args = parser.parse_args()

    server = await asyncio.start_server(partial(connection, args.connect_host, args.connect_port, args.http_inject, args.http_connect), args.listen_host, args.listen_port)

    async with server:
        await server.serve_forever()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
