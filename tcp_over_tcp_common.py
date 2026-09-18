from __future__ import annotations
from collections.abc import Callable as caCallable
from collections import *
from dataclasses import *
from functools import *
from itertools import *
from operator import *
from typing import *
from enum import *
import argparse
import asyncio
import base64
import contextlib
import errno
import fractions
import io
import ipaddress
import json
import logging
import math
import os
import pathlib
import random
import socket
import sys
import textwrap
import time
import traceback
import types
import typing
import uuid
import abc
import zlib

############################################################################################################################

uuid_bytes_size = len(uuid.uuid4().bytes)

############################################################################################################################

async def async_raise(e: BaseException) -> NoReturn:
    raise e

############################################################################################################################

def terminate(message: str) -> NoReturn:
    # Call it when it seems that this branch is unreachable.
    # asyncio cannot find the difference
    # between KeyboardInterrupt from SIGINT and from here.
    # In both cases it would stop event loop
    # and reraise this exception from `asyncio.run()` invocation.
    # Not using `Exception`-based exceptions, because asyncio would
    # print `Unhandled exception` to stderr without actually stopping.
    raise KeyboardInterrupt(message)

############################################################################################################################

def can_use_event_loop() -> bool:
    try:
        asyncio.get_running_loop()
    except RuntimeError:
        return False
    else:
        return True

############################################################################################################################

if sys.version_info >= (3, 10) and TYPE_CHECKING:
    from _typeshed import DataclassInstance
else:
    DataclassInstance = Any

############################################################################################################################

if sys.version_info < (3, 10):
    def call(obj: Any, /, *args: Any, **kwargs: Any) -> Any:
        return obj(*args, **kwargs)

elif sys.version_info < (3, 11):
    call_R = TypeVar("call_R")
    call_P = ParamSpec("call_P")
    def call(obj: caCallable[call_P, call_R], /, *args: call_P.args, **kwargs: call_P.kwargs) -> call_R:
        return obj(*args, **kwargs)

else:
    from operator import call

############################################################################################################################

if sys.version_info < (3, 10):
    typed_cache_T = TypeVar("typed_cache_T", bound=Callable[..., Any])
    def typed_cache(func: typed_cache_T) -> typed_cache_T:
        return cast(typed_cache_T, cache(func))
else:
    typed_cache_R = TypeVar("typed_cache_R")
    typed_cache_P = ParamSpec("typed_cache_P")
    def typed_cache(func: caCallable[typed_cache_P, typed_cache_R]) -> caCallable[typed_cache_P, typed_cache_R]:
        return cast(caCallable[typed_cache_P, typed_cache_R], cache(func))

############################################################################################################################

checking_cast_t = TypeVar('checking_cast_t')

def checking_cast(t: type[checking_cast_t], val: Any) -> checking_cast_t:
    assert isinstance(val, t)
    return val

############################################################################################################################

tasks : set[asyncio.Task[None]] = set()

def fire(coro: typing.Awaitable[Any], halt_on_exception: bool = True) -> None:
    if not can_use_event_loop():
        terminate(f"Attempt to call `fire()` without event loop.")
    async def wrapper() -> None:
        try:
            await coro
        except asyncio.CancelledError:
            raise
        except BaseException as e:
            if halt_on_exception:
                terminate(f"Background task failed: {type(e).__name__}({e})")
            else:
                # asyncio would print it to console and ignore
                raise

    task : asyncio.Task[Any] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

############################################################################################################################

_gather_awaitable_wrapper_t = TypeVar('_gather_awaitable_wrapper_t')

def _gather_awaitable_wrapper(awaitable: Awaitable[_gather_awaitable_wrapper_t]) -> asyncio.Task[_gather_awaitable_wrapper_t]:
    async def wrapper() -> _gather_awaitable_wrapper_t:
        return await awaitable
    return asyncio.create_task(wrapper())

async def _gather_impl(*awaitables: Awaitable[Any]) -> tuple[Any, ...]:
    tasks = [
        _gather_awaitable_wrapper(awaitable)
        for awaitable in awaitables
    ]
    try:
        return tuple(await asyncio.gather(*tasks))
    finally:
        for task in tasks:
            task.cancel()
        await asyncio.gather(*tasks, return_exceptions=True)

gather_t1_t = TypeVar('gather_t1_t')
gather_t2_t = TypeVar('gather_t2_t')
gather_t3_t = TypeVar('gather_t3_t')
gather_t4_t = TypeVar('gather_t4_t')
gather_t5_t = TypeVar('gather_t5_t')
gather_t6_t = TypeVar('gather_t6_t')
gather_t7_t = TypeVar('gather_t7_t')
gather_t8_t = TypeVar('gather_t8_t')
gather_t9_t = TypeVar('gather_t9_t')

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], /) -> tuple[gather_t1_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], /) -> tuple[gather_t1_t, gather_t2_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], v8: Awaitable[gather_t8_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t, gather_t8_t]:
    ...

@overload
async def gather_and_cancel(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], v8: Awaitable[gather_t8_t], v9: Awaitable[gather_t9_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t, gather_t8_t, gather_t9_t]:
    ...

async def gather_and_cancel(*coro: Awaitable[Any]) -> tuple[Any, ...]:
    return tuple(await _gather_impl(*coro))

############################################################################################################################

import tcp_over_tcp_transport

@dataclass
class connection:
    connection_id: uuid.UUID
    transport: tcp_over_tcp_transport.ITransport
    queue: asyncio.Queue[bytes] = field(default_factory=asyncio.Queue)
    is_routed: asyncio.Event = field(default_factory=asyncio.Event)


async def route(routes: dict[uuid.UUID, connection], conn: connection, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    routes[conn.connection_id] = conn
    try:
        conn.is_routed.set()
        async def to_transport() -> None:
            while (data := await reader.read(2**16)):
                await conn.transport.write(data)
            await conn.transport.write(data)

        async def from_transport() -> None:
            while (data := await conn.queue.get()):
                writer.write(data)
                await writer.drain()
            writer.write_eof()

        await gather_and_cancel(
            to_transport(),
            from_transport(),
        )
    finally:
        del routes[conn.connection_id]

async def parse_input_messge(transport: tcp_over_tcp_transport.ITransport) -> tuple[uuid.UUID, bytes]:
    data = await transport.read()
    if len(data) < uuid_bytes_size:
        raise ValueError(f"Got small chunk: {data = !r}")
    return uuid.UUID(bytes=data[:uuid_bytes_size]), data[uuid_bytes_size:]

