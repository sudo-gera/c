import asyncio
import stream
import sys
import timeout
import time

@stream.streamify
async def connection(sock: stream.Stream):
    print(sock.transport.get_write_buffer_limits())
    l = 0
    while 1:
        c = await sock.read(1)
        if not c:
            break
        l += 1
        if l % 10000 == 0:
            print('\x1b[s\x1b[999;80H'+f'{l:020_d}'+'\x1b[u', end='')
        sys.stdout.flush()
        await asyncio.sleep(0.0000001)

async def loop_check():
    ct = time.monotonic_ns()
    while 1:
        await asyncio.sleep(0.1)
        a = ct
        ct = time.monotonic_ns()
        assert ct - a < 11 * 10**7
        print('\x1b[s\x1b[999;160H'+f'loop_is_ok'+'\x1b[u', end='')
        await asyncio.sleep(0.1)
        print('\x1b[s\x1b[999;160H'+f'          '+'\x1b[u', end='')
        sys.stdout.flush()
        ct = time.monotonic_ns()

async def client():
    await asyncio.sleep(0.1)
    async with stream.Stream(await asyncio.open_connection('127.0.0.1', 8888)) as sock:
        for q in range(1000):
            sock.write(b'-'*1_000_0)
            print('\ndone writing', q)
            print('\n1->', sock.transport.get_write_buffer_size())
            try:
                await timeout.run_with_timeout(sock.drain(), 0.1)
                # await sock.drain()
                print('\ndrained!')
            except asyncio.TimeoutError:
                print('\ntimeout')
            print('\n2->', sock.transport.get_write_buffer_size())

async def main():
    asyncio.create_task(loop_check())
    asyncio.create_task(client())
    async with await asyncio.start_server(connection, None, 8888) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())
