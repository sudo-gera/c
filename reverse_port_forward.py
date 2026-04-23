import asyncio
import argparse
import random

import asyncio
import traceback
import typing

T = typing.TypeVar('T')

async def run_with_timeout(coro: typing.Coroutine[typing.Any, typing.Any, T], timeout: float) -> T:
    task = asyncio.create_task(coro)
    e = None
    try:
        await asyncio.wait([task], timeout=timeout)
    except BaseException as _e:
        e=_e
    finally:
        if task.done():
            if e is not None:
                raise e
            return task.result()
        task.cancel()
    if e is not None:
        raise e
    raise asyncio.TimeoutError

background_tasks = set()
def fire(c):
    task = asyncio.create_task(c)
    background_tasks.add(task)
    task.add_done_callback(background_tasks.discard)

parser = argparse.ArgumentParser()
parser.add_argument('--tcp-listen', default=':0')
parser.add_argument('--cmd-listen', default=':0')
parser.add_argument('--tcp-connect', default=':0')
parser.add_argument('--cmd-connect', default=':0')
args = parser.parse_args()

cmd_connect = [(a,int(s)) for a,s in [args.cmd_connect.split(':')]][0]
cmd_listen = [(a,int(s)) for a,s in [args.cmd_listen.split(':')]][0]
tcp_connect = [(a,int(s)) for a,s in [args.tcp_connect.split(':')]][0]
tcp_listen = [(a,int(s)) for a,s in [args.tcp_listen.split(':')]][0]

assert bool(cmd_connect[0]) == bool(tcp_connect[0])
assert bool(cmd_listen[0]) == bool(tcp_listen[0])
assert bool(cmd_listen[0]) != bool(cmd_connect[0])

async def copy(r: asyncio.StreamReader, w: asyncio.StreamWriter):
    while data:= await r.read(2**16):
        w.write(data)
        await w.drain()
    w.write_eof()
    w.close()
    await w.wait_closed()

async def run_server(server):
    async with server:
        await server.serve_forever()

cmd = []

tasks = {}

async def handle_cmd(r: asyncio.StreamReader, w: asyncio.StreamWriter):
    global cmd
    t = int.from_bytes(await r.readexactly(8), 'big')
    if t == 0:
        cmd = [r,w]
        await asyncio.Future()
    elif t == 1:
        w.write((1).to_bytes(8, 'big'))
        await w.drain()
        w.close()
        await w.wait_closed()
    else:
        rt, wt = tasks[t]
        rc, wc = r, w
        await asyncio.gather(
            copy(rt, wc),
            copy(rc, wt),
        )


async def handle_tcp(r: asyncio.StreamReader, w: asyncio.StreamWriter):
    t = random.randint(2, 2**64-1)
    tasks[t] = [r,w]
    cmd[1].write(t.to_bytes(8, 'big'))
    await cmd[1].drain()



async def handle(t: int):
    rc,wc = await asyncio.open_connection(*cmd_connect)
    wc.write(t.to_bytes(8, 'big'))
    await wc.drain()
    rt,wt = await asyncio.open_connection(*tcp_connect)
    await asyncio.gather(
        copy(rt, wc),
        copy(rc, wt),
    )

current_connector_id = 0

async def connector():
    global current_connector_id
    current_connector_id += 1
    connector_id = current_connector_id
    try:
        r,w = await asyncio.open_connection(*cmd_connect)
        if connector_id != current_connector_id: return
        w.write((0).to_bytes(8, 'big'))
        await w.drain()
        if connector_id != current_connector_id: return
        while 1:
            t = int.from_bytes(await r.readexactly(8), 'big')
            fire(handle(t))
            if connector_id != current_connector_id: return
    except Exception as e:
        print(type(e), e)
        if isinstance(e, OSError) and e.errno == 24:
            exit()


async def main():
    if cmd_listen[0]:
        await asyncio.gather(
            run_server(await asyncio.start_server(handle_cmd, *cmd_listen)),
            run_server(await asyncio.start_server(handle_tcp, *tcp_listen)),
        )
    else:
        while 1:
            fire(run_with_timeout(connector(), 2))
            await asyncio.sleep(1)



if __name__ == '__main__':
    asyncio.run(main())
