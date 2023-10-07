from h import *
import sys
sys.setrecursionlimit(80)

def get_rec_depth(max = 99):
    try:
        return 1 + get_rec_depth(max - 1)
    except RecursionError:
        return 0

import asyncio

class deep_recursion:
    def __init__(self, f):
        self.f = f

    async def __call__(self, *a, **s):
        q = asyncio.Queue()
        asyncio.create_task(self.run(q, a, s))
        return await q.get()

    async def run(self, q, a, s):
        q.put_nowait(await self.f(*a, **s))



@deep_recursion
async def test4(n):
    print(asyncio.run(test4(n-20)))
    print(get_rec_depth())
    if n == 0:
        return 1
    return await test4(n - 1) * n

print(asyncio.run(test4(50)))
