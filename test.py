from h import *
import asyncio
import operator
import inspect

it = None

async def put_it(coro):
    coro = await coro
    global it
    it = coro
    return it
class post_await:
    def __init__(self, f):
        self.f = f
        if inspect.isawaitable(f):
            global it
            it = put_it(f)
    def __call__(self, *a, **s):
        if self.f is None:
            self.a=(a,s)
            return self
        if inspect.isawaitable(self.f):
            return self.ofc(*a, **s)
        else:
            global it
            res = self.f(*a, **s)
            if inspect.isawaitable(res):
                res = put_it(res)
            it = res
            return post_await(it)
    async def __coro__(self):
        return await self.f
    def __await__(self):
        return self.__coro__().__await__()
    def ofc(self, v):
        return v
    def __mul__(self, oth):
        if isinstance(oth, post_await):
            return post_await(oth.a[0][0])
        return oth
    def __rmul__(self, oth):
        if hasattr(self, 'a'):
            return type(self)(oth)(*self.a[0], **self.a[1])
        return type(self)(oth)

btw = post_await(None)

@post_await
async def test(i):
    asyncio.sleep*btw(random.random())*btw(await it)
    return i


async def get(i):
    assert await test(i) == i
    assert test(i).ofc(await it) == i
    return i
    

@asyncio.run
@operator.methodcaller('__call__')
async def main():
    assert asyncio.gather(
        *map(get, range(20))
    )*btw*btw(await it)*it.__str__() == str([*range(20)])