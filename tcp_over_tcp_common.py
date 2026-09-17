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

def fire(coro: typing.Awaitable[Any]) -> None:
    async def wrapper() -> None:
        try:
            await coro
        except BaseException:
            raise KeyboardInterrupt

    task : asyncio.Task[Any] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

gather_t_t = TypeVar('gather_t_t')
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
async def gather(v1: Awaitable[gather_t1_t], /) -> tuple[gather_t1_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], /) -> tuple[gather_t1_t, gather_t2_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t]:
    ...

@overload
async def gather(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], v8: Awaitable[gather_t8_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t, gather_t8_t]:
    ...

async def gather(*coro: Awaitable[Any]) -> tuple[Any, ...]:
    return tuple(await asyncio.gather(*coro))

############################################################################################################################

@dataclass(frozen=True)
class Config:
    alive_interval: float
    count_max: float
    cache_chunks: int

@dataclass
class _TransportChunked(abc.ABC):
    __reader: asyncio.StreamReader
    __writer: asyncio.StreamWriter

    async def __write_chunk(self, data: bytes, drain: bool) -> None:
        self.__writer.write(data)
        if drain:
            await self.__writer.drain()

    async def __read_chunk(self, len: int) -> bytes:
        return await self.__reader.readexactly(len)

    async def aclose(self) -> None:
        self.__writer.close()
        await self.__writer.wait_closed()

@dataclass
class _TransportSized(abc.ABC):
    __wrapped: _TransportChunked

    async def __write_sized(self, data: bytes | int, drain: bool) -> None:
        if isinstance(data, int):
            encoded = 2**64 + ~data
            if not data < encoded:
                raise ValueError(f"Value of {data = } is too big.")
            await self.__wrapped.__write_chunk(encoded.to_bytes(8, 'big'), drain=drain)
        else:
            await self.__wrapped.__write_chunk(len(data).to_bytes(8, 'big'), drain=False)
            await self.__wrapped.__write_chunk(data, drain=drain)

    async def __read_sized(self) -> bytes | int:
        size = int.from_bytes(await self.__wrapped.__read_chunk(8), 'big')
        decoded = 2**64 + ~size
        if decoded < size:
            return decoded
        return await self.__wrapped.__read_chunk(size)

    async def aclose(self) -> None:
        await self.__wrapped.aclose()

@dataclass
class TransportKeepAlive(abc.ABC):
    __wrapped: _TransportSized
    __conf: Config
    __on_recv: Callable[[bytes], None]
    __send_queue: asyncio.Queue[bytes]
    __last_alive: float = field(default_factory=time.monotonic)

    async def __write_loop(self) -> None:
        while True:
            data = await self.__send_queue.get()
            await self.__wrapped.__write_sized(data, True)

    async def __write_alive_loop(self) -> None:
        while True:
            await self.__wrapped.__write_sized(0, drain=True)
            await asyncio.sleep(self.__conf.alive_interval)

    async def __read_loop(self) -> None:
        while True:
            data = await self.__wrapped.__read_sized()
            if isinstance(data, bytes):
                self.__on_recv(data)
                continue
            if data == 0:
                self.__last_alive = time.monotonic()
            raise ValueError(f"Unknown value for {data = !r}")

    async def __check_loop(self) -> None:
        while True:
            current_time = time.monotonic()
            if current_time - self.__last_alive > self.__conf.alive_interval * ( self.__conf.count_max + 1 ):
                raise TabError

    async def loop(self) -> None:
        # try:
        await gather(
            self.__write_loop(),
            self.__write_alive_loop(),
            self.__read_loop(),
            self.__check_loop(),
        )
        # finally:
        #     self.aclose()

    async def aclose(self) -> None:
        await self.__wrapped.aclose()

@dataclass
class _MultiTransport:
    conf: Config
    on_recv: Callable[[bytes], None]
    __send_queue: asyncio.Queue[bytes] = field(default_factory=partial(asyncio.Queue, maxsize=8))

    async def run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        transport = TransportKeepAlive(
            _TransportSized(
                _TransportChunked(
                    reader,
                    writer,
                ),
            ),
            self.conf,
            self.on_recv,
            self.__send_queue,
        )
        await transport.loop()

    async def write(self, data: bytes) -> None:
        await self.__send_queue.put(data)

@dataclass
class _DeliveryMessagesTransport:
    conf: Config
    on_recv_data: Callable[[int, bytes], None]
    on_recv_ack: Callable[[int], None]
    __wrapped: _MultiTransport = cast(_MultiTransport, ...)

    def __on_recv(self, data: bytes) -> None:
        index, data = int.from_bytes(data[:8], 'big'), data[8:]
        ack_index = 2**64 + ~index
        if ack_index < index:
            self.on_recv_ack(ack_index)
        else:
            self.on_recv_data(ack_index, data)

    def __post_init__(self) -> None:

        self.__wrapped = _MultiTransport(
            self.conf,
            self.__on_recv,
        )

    async def write_data(self, index: int, data: bytes) -> None:
        await self.__wrapped.write(index.to_bytes(8, 'big') + data)

    async def write_ack(self, index: int) -> None:
        await self.__wrapped.write((2**64 + ~index).to_bytes(8, 'big'))

    async def run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        return await self.__wrapped.run(reader, writer)

@dataclass
class RecvBuffer:
    size: int

    __data: dict[int, bytes] = field(default_factory=dict)
    __event = field(default_factory=asyncio.Event)
    __consumed = 0

    def __notify(self) -> None:
        self.__event.set()
        self.__event.clear()

    def maybe_add_to_cache(self, index: int, data: bytes) -> None:
        if index < self.__consumed:
            return
        self.__data[index] = data
        if len(self.__data) > self.size * 2:
            self.__data = dict(
                sorted(
                    self.__data.items()
                )[:self.size]
            )
        self.__notify()

    async def read(self) -> bytes:
        while True:
            if self.__consumed in self.__data:
                value = self.__data.pop(self.__consumed)
                self.__consumed += 1
                self.__notify()
                return value
            await self.__event.wait()

@dataclass
class SendBuffer:
    size: int

    __data: dict[int, bytes] = field(default_factory=dict)
    __externally_written: int = 0
    __event = field(default_factory=asyncio.Event)
    __last_selected: int = 0

    def __notify(self) -> None:
        self.__event.set()
        self.__event.clear()

    async def write(self, data: bytes) -> None:
        index = self.__externally_written
        self.__externally_written += 1

        while True:
            if len(self.__data) < self.size:
                self.__data[index] = data
                self.__notify()
                return
            await self.__event.wait()

    def mark_as_delivered(self, index: int) -> None:
        self.__data.pop(index, None)
        self.__notify()
    
    async def select_message_to_send(self) -> tuple[int, bytes]:

        for attempt in range(self.__last_selected+1, self.__externally_written):
            if attempt in self.__data:
                self.__last_selected = attempt
                return self.__last_selected, self.__data[self.__last_selected]

        while not self.__data:
            await self.__event.wait()
        
        self.__last_selected = min(self.__data.keys())
        return self.__last_selected, self.__data[self.__last_selected]

class RetryTransport:
    conf: Config

    __send_buffer: SendBuffer = cast(SendBuffer, ...)
    __recv_buffer: RecvBuffer = cast(RecvBuffer, ...)
    __wrapped: _DeliveryMessagesTransport = cast(_DeliveryMessagesTransport, ...)

    def __on_recv_data(self, index: int, data: bytes) -> None:
        self.__recv_buffer.maybe_add_to_cache(index, data)
        fire(self.__wrapped.write_ack(index))

    def __on_recv_ack(self, index: int) -> None:
        self.__send_buffer.mark_as_delivered(index)

    def __post_init__(self) -> None:
        self.__send_buffer = SendBuffer(self.conf.cache_chunks)
        self.__recv_buffer = RecvBuffer(self.conf.cache_chunks)
        self.__wrapped = _DeliveryMessagesTransport(
            self.conf,
            self.__on_recv_data,
            self.__on_recv_ack,
        )
        fire(self.__loop())

    async def run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        return await self.__wrapped.run(reader, writer)

    async def __internal_send_loop(self) -> None:
        while True:
            index, data = await self.__send_buffer.select_message_to_send()
            await self.__wrapped.write_data(index, data)
    
    async def read(self) -> bytes:
        return await self.__recv_buffer.read()
    
    async def write(self, data: bytes) -> None:
        await self.__send_buffer.write(data)

    async def __loop(self) -> None:
        await gather(
            self.__internal_send_loop(),
        )

transports: defaultdict[bytes, RetryTransport] = defaultdict(RetryTransport)

