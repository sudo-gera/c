from __future__ import annotations
import asyncio.selector_events
import datetime
import asyncio
import time
import sys
import random
import argparse
from dataclasses import dataclass
from typing import *
import psutil
import itertools
import traceback
from collections import defaultdict

###################################

exit_queue : asyncio.Queue[None] = asyncio.Queue()

async def put_exit_queue_on_error(coro: Coroutine[Any, Any, Any]) -> None:
    try:
        await coro
    except Exception as e:
        exc = traceback.format_exc()
        print(exc)
        exit_queue.put_nowait(None)

background_tasks = set()

def fire(coro: Coroutine[Any, Any, Any]) -> None:
    task = asyncio.create_task(put_exit_queue_on_error(coro))
    background_tasks.add(task)
    task.add_done_callback(background_tasks.discard)

###################################

@dataclass(frozen=True)
class way:
    username: str
    server: str

###########################

async def can_bind(host: str, port: int) -> bool:
    try:
        async with await asyncio.start_server(print, host, port) as server:
            pass
        return True
    except Exception:
        return False

###################################

def get_usernames(args: main_args) -> list[str]:
    now = datetime.datetime.now()
    one_day = datetime.timedelta(days=1)
    return [
        (offset * one_day + now).strftime(args.username_strftime)
        for offset in range(-args.days_before, args.days_after + 1)
    ]

def get_ways(args: main_args) -> list[way]:
    return [
        way(username=username, server=server)
        for server, username in itertools.product(
            args.servers,
            get_usernames(args),
        )
    ]

###########################

ways_status : defaultdict[way, int] = defaultdict(int)

way_by_internal_port : dict[int, tuple[way, int]] = {}

async def regular_checker(args: main_args) -> None:
    global ways_up
    while 1:
        await asyncio.sleep(0.1)
        ways_up_local = set()

        async def process(port: int, way: way, st: int, ct: int) -> None:
            if not await can_bind(args.host, port):
                print(f'==== connection is up: {port = } {way = } {st = } {ct = }')
                ways_up_local.add(way)
                print(f'==== + {ways_up_local = } {id(ways_up_local)}')
                way_by_internal_port[port] = (way, ct)
            else:
                if ct - st > 16 * 10**9:
                    print(f'==== releasing {port = } from {way = } {st = } {ct = }')
                    way_by_internal_port.pop(port, None)

        ct = time.monotonic_ns()

        await asyncio.gather(
            *[
                process(port, way, st, ct)
                for port, [way, st] in [*way_by_internal_port.items()]
            ]
        )

        print(f'==== {ways_up_local = }  {id(ways_up_local)}')
        for way in get_ways(args):
            if way in ways_up_local:
                print(f'==== incrementing {way = } {ways_status[way] = }')
                ways_status[way] = min(ways_status[way] + 1, 4)
            else:
                ways_status[way] = max(ways_status[way] - 1, 0)

###########################

async def stop_process(process: asyncio.subprocess.Process) -> None:
    try:
        process.terminate()
    except ProcessLookupError:
        return
    await asyncio.sleep(0.1)
    try:
        process.kill()
    except ProcessLookupError:
        return

async def try_way(args: main_args, way: way) -> None:
    internal_port = ({*range(args.lower_internal_port, args.upper_internal_port+1)} - {*way_by_internal_port}).pop()
    assert internal_port not in way_by_internal_port
    way_by_internal_port[internal_port] = (way, time.monotonic_ns())
    print(f'==== aquiring {internal_port = } for {way_by_internal_port[internal_port]}')
    print(f'==== starting {way = } {internal_port = }')
    process = await asyncio.create_subprocess_exec(
        f'sshpass',
        f'-p', args.password,
        f'ssh',f'_',
        f'-N',
        f'-oDynamicForward={args.host:s}:{args.port:d}',
        f'-oDynamicForward={args.host:s}:{internal_port:d}',
        f'-oServerAliveInterval={args.server_alive_interval:d}',
        f'-oExitOnForwardFailure=yes',
        f'-oConnectTimeout={args.connect_timeout:d}',
        f'-oConnectionAttempts=1',
        f'-oServerAliveCountMax=1',
        f'-oPasswordAuthentication=yes',
        f'-oCompression=yes',
        f'-oStrictHostKeyChecking=no',
        f'-oUserKnownHostsFile=/dev/null',
        # f'-oLogLevel=DEBUG3',
        f'-oUser={way.username:s}',
        f'-oHostname={way.server:s}',
        f'-oPort={args.server_port:d}',
        stdin=asyncio.subprocess.PIPE,
        # stdout=asyncio.subprocess.PIPE,
        # stderr=asyncio.subprocess.PIPE,
    )
    print(f'==== started {way = }')
    try:
        await process.communicate()
    finally:
        fire(stop_process(process))

###################################

async def regular_launcher(args: main_args) -> None:
    timeout = 0.0
    successful_binds = 0
    while True:
        await asyncio.sleep(timeout)
        ways_up = [w for w,c in ways_status.items() if c]
        if await can_bind(args.host, args.port):
            successful_binds += 1
            print(f'==== {ways_up = } {successful_binds = }')
            if ways_up and successful_binds < 8:
                print(f'==== can bind {args.host}:{args.port}, selecting up way')
                timeout = 2
                selected_way = random.choice([*ways_up])
                print(f'{selected_way = }')
                fire(try_way(args, selected_way))
            else:
                print(f'==== can bind {args.host}:{args.port}, selecting random way')
                timeout = 0.1
                selected_way = random.choice(get_ways(args))
                print(f'{selected_way = }')
                fire(try_way(args, selected_way))
        else:
            print(f'==== cannot bind {args.host}:{args.port}, {ways_up = }')
            timeout = 0.1
            successful_binds = 0

async def main(args: main_args) -> None:
    assert len(get_ways(args)) * 4 <= len(range(args.lower_internal_port, args.upper_internal_port+1))
    fire(regular_launcher(args))
    fire(regular_checker(args))
    await exit_queue.get()

###########################

@dataclass(frozen=True)
class main_args:
    password: str
    username_strftime: str
    days_after: int
    days_before: int
    servers: list[str]
    host: str
    port: int
    connect_timeout: int
    server_alive_interval: int
    server_port: int
    lower_internal_port: int
    upper_internal_port: int


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--password', required=True)
    parser.add_argument('--servers', required=True, nargs='+')
    parser.add_argument('--username-strftime', required=True)
    parser.add_argument('--days-after', required=True, type=int)
    parser.add_argument('--days-before', required=True, type=int)
    parser.add_argument('--host', required=True)
    parser.add_argument('--port', required=True, type=int)
    parser.add_argument('--server-alive-interval', required=True, type=int)
    parser.add_argument('--connect-timeout', required=True, type=int)
    parser.add_argument('--server-port', required=True, type=int)
    parser.add_argument('--lower-internal-port', required=True, type=int)
    parser.add_argument('--upper-internal-port', required=True, type=int)

    args = parser.parse_args()

    try:
        asyncio.run(main(main_args(**vars(args))))
    except KeyboardInterrupt:
        pass
