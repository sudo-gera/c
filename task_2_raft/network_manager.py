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

term_size = [*map(int, sys.argv[1:3])]
assert len(hosts) == 8

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
    r,w = await asyncio.open_connection(host, 2100)
    try:
        w.write(c.encode())
        w.write_eof()
        await w.drain()
        print(await r.read())
    finally:
        await common.safe_socket_close(w)

async def change_network_config() -> None:
    net_map : dd[int, dict[int, bool]] = dd(dict)
    for i in range(len(hosts)):
        for o in range(i+1):
            net_map[i][o] = net_map[o][i] = random.randint(0, 4) == 0
    for h in range(len(hosts)):
        if host_status[h][0]:
            host_status[h][1] = random.randint(0, 8) == 0
        else:
            host_status[h][1] = random.randint(0, 8) != 0
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
            for w in range(m//(2-(host_status[h][0]^host_status[h][1]))):
                dots.append(
                    (
                        hosts_dots[h] + cmath.rect(1, cmath.pi*2/m*q)*w/m/20,
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
        dot/=1.3
        dot/=2
        dot += 0.5 + 0.5j
        dot *= width
        x = max(min(int(dot.real), width-1), 0)
        y = max(min(int(dot.imag), width-1), 0)
        assert x in range(width)
        assert y in range(width)
        canvas[x//2][y][0][x%2] = True
        canvas[x//2][y][1][x%2] = c
    print(
        '\n'.join([
            ''.join(
                [
                    get_colored_symbol(canvas[q][w][0][0], canvas[q][w][0][1], canvas[q][w][1][0], canvas[q][w][1][1])
                    for w in range(width)
                ]
            )
            for q in range(len(canvas))
        ])
    )
    async def send_tables(h: int) -> None:
        await send_command(f'echo {base64.b64encode(tables[h].encode()).decode()} | base64 -d | iptables-restore', hosts[h])
    async def send_status(h: int) -> None:
        command = 'true'
        if host_status[h][1]:
            if host_status[h][0]:
                command = "rm /work ; kill $(ps ax | grep -E 'solution.py|tail -f //dev/null' | awk '{print $1}')"
                host_status[h][0]=False
            else:
                command = "touch /work ; kill $(ps ax | grep -E 'solution.py|tail -f //dev/null' | awk '{print $1}')"
                # command = "python3.11 /solution.py $(cat /hosts.txt)"
                host_status[h][0]=True
        await send_command(command, hosts[h])
    [*
        map(
            fire,
            map(
                send_status,
                range(
                    len(
                        hosts
                    )
                )
            )
        )
    ]
    await asyncio.gather(
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
    while 1:
        await change_network_config()
        await asyncio.sleep(15)

if __name__ == '__main__':
    asyncio.run(main())
