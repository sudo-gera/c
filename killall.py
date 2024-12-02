import os
import time
import re
import bisect
from collections import defaultdict as dd
import signal
import sys

def parse_ps_and_get_popular_process(text: bytes) -> tuple[bytes, list[bytes]]:
    a = text.split(b'\n')
    cols_str = a[0]
    a = [q for q in a[1:] if q]
    s = [q for q in range(len(cols_str)) if all([w[q:q+1].isspace() for w in a])]
    d : list[None|int] = [None, None]
    d[1:-1] = [s[bisect.bisect_left(s, q) - len(s)]
        for q in range(len(cols_str))
        if not cols_str[q:q+1].isspace() and (cols_str[q+1:q+2]+b' ').isspace()
    ][:-1]
    f=[[w[b:e] for b, e in zip(d, d[1:])] for w in a]
    cols = {v:k for k,v in enumerate(cols_str.split())}
    for q in cols.values():
        while all([w[q][:1].isspace() for w in f]):
            for w in f:
                w[q] = w[q][1:]
        while all([w[q][-1:].isspace() for w in f]):
            for w in f:
                w[q] = w[q][:-1]
    g : dd[bytes, list[bytes]] = dd(list)
    for w in f:
        g[w[cols[b'CMD']]].append(w[cols[b'PID']])
    return max(g.items(), key=lambda a:len(a[1]))


while 1:
    pipe = os.pipe()
    pid = os.fork()
    if not pid:
        time.sleep(20)
        os.close(pipe[0])
        os.dup2(pipe[1], 1)
        os.close(pipe[1])
        os.execlp('ps','ps','-ax')
    else:
        os.close(pipe[1])
        a = bytearray()
        d = b'-'
        while d:
            d = os.read(pipe[0], 2**16)
            a.extend(d)
        os.waitpid(pid, 0)
        os.close(pipe[0])
        g = parse_ps_and_get_popular_process(bytes(a))
        if len(g[1]) > 256:
            print(time.asctime(), f'found {g[0]!r} having {len(g[1])} processes')
            for pid in map(int, g[1]):
                try:
                 os.kill(pid, signal.SIGTERM)
                except Exception as e:
                 print(type(e), e)
            if len(sys.argv) == 2:
                os.system(sys.argv[1])




