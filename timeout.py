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
