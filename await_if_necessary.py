import asyncio
import inspect
from typing import *

T = TypeVar('T')

@overload
def await_if_necessary(value: Awaitable[T]) -> Awaitable[T]: # type: ignore[overload-overlap]
    ...

@overload
def await_if_necessary(value: T) -> asyncio.Future[T]:
    ...

def await_if_necessary(value: Awaitable[T] | T) -> Awaitable[T] | asyncio.Future[T]:
    if inspect.isawaitable(value):
        a_value = value
    else:
        a_value = asyncio.Future()
        a_value.set_result(value)
    return a_value
