import ipaddress
import common
import asyncio
import sys
import random
import textwrap
import base64
import cmath
import os
import typing
import math
import logging
import time
from collections import defaultdict as dd

##############################################################################################################################################

tasks : set[asyncio.Task[None]] = set()

def fire(coro: typing.Generator[typing.Any, None, None] | typing.Coroutine[typing.Any, typing.Any, None]) -> None:
    task : asyncio.Task[None] = asyncio.create_task(coro)
    tasks.add(task)
    task.add_done_callback(tasks.discard)

##############################################################################################################################################

hosts = sys.argv[3:]
hosts.sort()
# my_ip = common.select_my_ip(hosts)
# other_hosts = {*hosts} - {my_ip}

##############################################################################################################################################

colors = [
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
    '\x1b[97m',
]
# my_color = colors[hosts.index(my_ip)]
clear_color = '\x1b[0m'


##############################################################################################################################################

async def connect_stdin_stdout() -> tuple[asyncio.StreamReader, asyncio.StreamWriter]:
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader()
    protocol = asyncio.StreamReaderProtocol(reader)
    # await loop.connect_read_pipe(lambda: protocol, sys.stdin)
    w_transport, w_protocol = await loop.connect_write_pipe(asyncio.streams.FlowControlMixin, sys.stdout)
    writer = asyncio.StreamWriter(w_transport, w_protocol, reader, loop)
    return reader, writer

out_queue : asyncio.Queue[str] = asyncio.Queue()

async def out_printer() -> None:
    stdin, stdout = await connect_stdin_stdout()
    while 1:
        data = await out_queue.get()
        while not out_queue.empty():
            data += out_queue.get_nowait()
        stdout.write(data.encode())
        await stdout.drain()

class queue_stream:
    def __init__(self, q: asyncio.Queue[str]) -> None:
        self.q = q
    
    def write(self, data: str) -> None:
        self.q.put_nowait(data)

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='[ %(asctime)s ]: %(message)s', stream=queue_stream(out_queue))

class log_stream:
    def __init__(self, logger_func: typing.Callable[[str], None]):
        self.logger_func = logger_func
        self.buffer = ''
    def write(self, data: str) -> None:
        self.buffer += data
        while '\n' in self.buffer:
            data, self.buffer = self.buffer.split('\n', 1)
            data = data + ' \x00 ' + f'{time.time_ns():024d}'
            self.logger_func(data)
            sys.stdout.flush()
            sys.stderr.flush()

debug_stream = log_stream(logging.debug)
info_stream = log_stream(logging.info)
error_stream = log_stream(logging.error)

##############################################################################################################################################


term_size = [*map(int, sys.argv[1:3])]
# assert len(hosts) == 8

'''
*filter
:INPUT ACCEPT [7:488]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [4:424]
-I INPUT -p tcp --dport 4444 -j DROP
-I OUTPUT -p tcp --sport 4444 -j DROP
COMMIT
'''

def get_colored_symbol(ue: bool, le: bool, uc: str, lc: str) -> str:
    if not ue and not le:
        return ' '
    if ue and not le:
        return uc + chr(9600) + clear_color
    if le and not ue:
        return lc + chr(9603) + clear_color
    ucp = uc[-2:-1]
    lcp = lc[-2:-1]
    if not ucp and not lcp:
        return chr(9608)
    if not ucp:
        return '\x1b[10'+lcp+'m'+chr(9600)+clear_color
    if not lcp:
        return '\x1b[10'+ucp+'m'+chr(9603)+clear_color
    return '\x1b[9'+ucp+';10'+lcp+'m'+chr(9600)+clear_color

host_status = [[False, False] for q in range(len(hosts))]

async def send_command(c: str, host: str) -> None:
    # print(c, host)
    r,w = await asyncio.open_connection(host, 2100)
    try:
        w.write(c.encode())
        w.write_eof()
        await w.drain()
        sys.stdout.buffer.write(await r.read())
        sys.stdout.buffer.flush()
    finally:
        await common.safe_socket_close(w)

async def change_network_config() -> None:
    net_map : dd[int, dict[int, bool]] = dd(dict)
    for h in range(len(hosts)):
        if host_status[h][0]:
            host_status[h][1] = random.randint(0, 2) == 0
        else:
            host_status[h][1] = random.randint(0, 4) != 0
    for i in range(len(hosts)):
        for o in range(i+1):
            if host_status[o][0]^host_status[o][1] and host_status[i][0]^host_status[i][1]:
                net_map[i][o] = net_map[o][i] = random.randint(0, 5) > 0
            else:
                net_map[i][o] = net_map[o][i] = False
    tables = [''] * len(hosts)
    for h in range(len(hosts)):
        tables[h] += textwrap.dedent(f'''
            *filter
            :INPUT ACCEPT [7:488]
            :FORWARD ACCEPT [0:0]
            :OUTPUT ACCEPT [4:424]
            ''')
    for i in range(len(hosts)):
        for o in range(len(hosts)):
            if i != o:
                if not net_map[i][o]:
                    tables[i] += textwrap.dedent(f'''
                        -I OUTPUT -p tcp --dport 4444 -d {hosts[o]} -j DROP
                        -I INPUT  -p tcp --dport 4444 -s {hosts[o]} -j DROP
                        ''')
                    tables[o] += textwrap.dedent(f'''
                        -I OUTPUT -p tcp --dport 4444 -d {hosts[i]} -j DROP
                        -I INPUT  -p tcp --dport 4444 -s {hosts[i]} -j DROP
                        ''')
    for h in range(len(hosts)):
        tables[h] += textwrap.dedent(f'''
            COMMIT
            ''')
    hosts_dots = [
        cmath.rect(
            1,
            (cmath.pi * 2 * (0.5 + h)/len(hosts)))
            for h in range(len(hosts)
        )
    ]
    dots = [(1j, '')][:0]
    m = 64
    for i in range(len(hosts)):
        for o in range(len(hosts)):
            if net_map[i][o]:
                for q in range(m*m//2, m*m):
                    dots.append(
                        (
                            hosts_dots[i] + (hosts_dots[o] - hosts_dots[i])*q/(m*m),
                            '',
                        )
                    )
    for h in range(len(hosts)):
        for q in range(m):
            for w in range(m//(1+3*(1^host_status[h][0]^host_status[h][1]))):
                dots.append(
                    (
                        hosts_dots[h] + cmath.rect(1, cmath.pi*2/m*q)*w/m/12,
                        colors[h],
                    )
                )
    width = min(term_size[0]*2, term_size[1])
    canvas = [
        [
            (
                [False, False],
                ['', '']
            )
            for w in range(width)
        ]
        for q in range(width//2+1)
    ]
    for dot, c in dots:
        # dot += 0.001 + 0.001j
        dot /= 1.1
        dot /= 2
        dot += 0.5 + 0.5j
        dot *= width
        x = max(min(math.floor(dot.real), width-1), 0)
        y = max(min(math.floor(dot.imag), width-1), 0)
        assert x in range(width)
        assert y in range(width)
        canvas[x//2][y][0][x%2] = True
        canvas[x//2][y][1][x%2] = c
    # print(
    #     '\n'.join([
    #         '\x00'+''.join(
    #             [
    #                 get_colored_symbol(canvas[q][w][0][0], canvas[q][w][0][1], canvas[q][w][1][0], canvas[q][w][1][1])
    #                 for w in range(width)
    #             ]
    #         )
    #         for q in range(len(canvas))
    #     ]) + '\x01'
    # )
    print(
        '\n'.join([
            '\x01'+''.join(
                [
                    get_colored_symbol(canvas[q][w][0][0], canvas[q][w][0][1], canvas[q][w][1][0], canvas[q][w][1][1])
                    for w in range(width)
                ]
            )
            for q in range(len(canvas))
        ]),
        file=info_stream
    )
    async def send_tables(h: int) -> None:
        await send_command(f'echo {base64.b64encode(tables[h].encode()).decode()} | base64 -d | iptables-restore', hosts[h])
    async def send_status(h: int) -> None:
        command = 'true'
        if host_status[h][1]:
            if host_status[h][0]:
                prefix = 'rm    '
                host_status[h][0]=False
            else:
                prefix = 'touch '
                host_status[h][0]=True
            command = prefix + "/work ; kill -9 $(ps ax | grep -E 'solution|tail -f //dev/null' | grep -v grep | awk '{print $1}')"
        await send_command(command, hosts[h])
    # [*
    #     map(
    #         fire,
    #         map(
    #             send_status,
    #             range(
    #                 len(
    #                     hosts
    #                 )
    #             )
    #         )
    #     )
    # ]
    # await asyncio.gather(
    #     *map(
    #         send_status,
    #         range(
    #             len(
    #                 hosts
    #             )
    #         )
    #     )
    # )
    await asyncio.gather(
        *map(
            send_status,
            range(
                len(
                    hosts
                )
            )
        ),
        *map(
            send_tables,
            range(
                len(
                    hosts
                )
            )
        )
    )


async def main() -> None:
    fire(out_printer())
    while 1:
        await change_network_config()
        await asyncio.sleep(4)

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
