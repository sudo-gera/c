import asyncio
import time
import random
import typing

class awaitable_event:
    def __init__(self) -> None:
        self.future : asyncio.Future[None] | None = None

    def __call__(self) -> None:
        if self.future is not None:
            self.future.set_result(None)
        self.future = None

    async def wait(self) -> None:
        if self.future is None:
            self.future = asyncio.Future()
        assert isinstance(self.future, asyncio.Future)
        await self.future
    
    def __await__(self) -> typing.Generator[None, None, None]:
        return self.wait().__await__()

event = awaitable_event()

def strtime() -> str:
    a = f'{time.time_ns()}'
    a = a[:-9] + '_' + a[-9:]
    return a

async def waiter() -> None:
    await asyncio.sleep(random.random() * 16)
    print(f'{strtime()} +')
    await event.wait()
    print(f'{strtime()} -')

async def event_generator() -> None:
    while 1:
        await asyncio.sleep(1)
        event()
        print(f'{strtime()} =')

async def main() -> None:
    await asyncio.gather(
        event_generator(),
        *[
            waiter()
            for q in range(80)
        ]
    )

asyncio.run(main())
