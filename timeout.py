import asyncio
import traceback
import typing

T = typing.TypeVar('T')

async def run_with_timeout(coro: typing.Coroutine[typing.Any, typing.Any, T], timeout: float) -> T:
    task = asyncio.create_task(coro)
    await asyncio.wait([task], timeout=timeout)
    if task.done():
        return task.result()
    task.cancel()
    raise asyncio.TimeoutError
