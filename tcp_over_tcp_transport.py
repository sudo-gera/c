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

@dataclass
class _reject_concurrent:
    __locked: bool = False

    def __enter__(self) -> None:
        if self.__locked:
            terminate(f"Internal invariant is broken")
        self.__locked = True

    def __exit__(self, *_: Any) -> None:
        if not self.__locked:
            terminate(f"Internal invariant is broken")
        self.__locked = False

@dataclass(frozen=True)
class Config:
    alive_interval: float
    max_keepalives_without_answer: int
    cache_chunks: int
    max_chunk_size: int

    def __post_init__(self) -> None:
        if self.alive_interval <= 0:
            raise ValueError("alive_interval must be > 0")
        if self.max_keepalives_without_answer < 0:
            raise ValueError("count_max must be >= 0")
        if self.cache_chunks <= 0:
            raise ValueError("cache_chunks must be > 0")
        if self.max_chunk_size <= 0:
            raise ValueError("max_chunk_size must be > 0")
        if self.max_chunk_size >= 2**64-1:
            raise ValueError("max_chunk_size must be < 2**64-1")

@dataclass
class _TransportChunked(abc.ABC):
    __reader: asyncio.StreamReader
    __writer: asyncio.StreamWriter

    async def write_chunk(self, data: bytes) -> None:
        self.__writer.write(data)
        await self.__writer.drain()

    async def read_chunk(self, size: int) -> bytes:
        return await self.__reader.readexactly(size)

@dataclass
class _TransportSized:
    conf: Config

    _wrapped: _TransportChunked
    __r_lock: _reject_concurrent = field(default_factory=_reject_concurrent)

    async def write_sized(self, data: bytes | None = None) -> None:
        if data is None:
            await self._wrapped.write_chunk(bytes([255]*8))
        else:
            data = len(data).to_bytes(8, 'big') + data
            await self._wrapped.write_chunk(data)

    async def read_sized(self) -> bytes | None:
        with self.__r_lock:
            size_b = await self._wrapped.read_chunk(8)
            if size_b == bytes([255]*8):
                return None
            size = int.from_bytes(size_b, 'big')
            if size > self.conf.max_chunk_size:
                raise ValueError(f"Chunk size is too big: {size = }.")
            return await self._wrapped.read_chunk(size)

@dataclass
class _TransportKeepAlive(abc.ABC):
    wrapped: _TransportSized
    conf: Config
    on_recv: Callable[[bytes], None]
    send_queue: asyncio.Queue[bytes]

    __last_alive: float = field(default_factory=time.monotonic)
    __alive_queue: asyncio.Queue[None] = field(default_factory=lambda: asyncio.Queue(maxsize=8))

    async def __write_loop(self) -> None:
        while True:
            data = await self.send_queue.get()
            await self.wrapped.write_sized(data)

    async def __queue_alive_loop(self) -> None:
        while True:
            if self.__alive_queue.full():
                # Queue full means task loop responsible for cleaning it is blocked in write() on socket.
                raise ValueError(f"Huge back pressure in socket when trying to send keep alive message.")
            self.__alive_queue.put_nowait(None)
            await asyncio.sleep(self.conf.alive_interval)

    async def __write_alive_loop(self) -> None:
        while True:
            await self.__alive_queue.get()
            await self.wrapped.write_sized()

    async def __read_loop(self) -> None:
        while True:
            data = await self.wrapped.read_sized()
            if data is None:
                self.__last_alive = time.monotonic()
            else:
                self.on_recv(data)
                continue

    async def __check_loop(self) -> None:
        while True:
            current_time = time.monotonic()
            max_delay_since_last_alive = self.conf.alive_interval * ( self.conf.max_keepalives_without_answer + 1 )
            until_timeout = self.__last_alive + max_delay_since_last_alive - current_time
            if until_timeout <= 0:
                raise RuntimeError(f"Timeout: No keepalive signals for {current_time - self.__last_alive} seconds.")
            await asyncio.sleep(until_timeout)

    async def loop(self) -> None:
        await gather_and_cancel(
            self.__write_loop(),
            self.__queue_alive_loop(),
            self.__write_alive_loop(),
            self.__read_loop(),
            self.__check_loop(),
        )

@dataclass
class _MultiTransport:
    conf: Config
    on_recv: Callable[[bytes], None]
    __send_queue: asyncio.Queue[bytes] = field(default_factory=lambda: asyncio.Queue(maxsize=8))

    async def no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # This function is allowed to be called in parallel by different streams.
        # We run until exception and caller is responsible for closing stream after this function exits
        transport = _TransportKeepAlive(
            _TransportSized(
                self.conf,
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
    _wrapped: _MultiTransport = cast(_MultiTransport, ...)

    def __on_recv(self, data: bytes) -> None:
        if len(data) < 9:
            # looks like would never happen
            raise KeyboardInterrupt(f"Internal invariant is broken: {len(data) = }")
        typ, index, data = int.from_bytes(data[0:1], 'big'), int.from_bytes(data[1:9], 'big'), data[9:]
        if typ:
            self.on_recv_ack(index)
        else:
            self.on_recv_data(index, data)

    def __post_init__(self) -> None:

        self._wrapped = _MultiTransport(
            self.conf,
            self.__on_recv,
        )

    async def write_data(self, index: int, data: bytes) -> None:
        await self._wrapped.write(b'\x00' + index.to_bytes(8, 'big') + data)

    async def write_ack(self, index: int) -> None:
        await self._wrapped.write(b'\x01' + index.to_bytes(8, 'big'))

    async def no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        return await self._wrapped.no_owning_run(reader, writer)

@dataclass
class lock_less_condition:
    _event: asyncio.Event = field(default_factory=asyncio.Event)

    def notify(self) -> None:
        # fires all futures from internal list
        self._event.set()
        # does not unfire them but clears the flag for new ones
        self._event.clear()

    async def wait(self) -> None:
        # 1. Creates future.
        # 2. Puts future into internal list.
        # only after that
        # 3. Releases event loop for other tasks by awaiting the future.
        await self._event.wait()

observable_data_t = TypeVar('observable_data_t')

@dataclass
class observable_data(Generic[observable_data_t]):
    _value: observable_data_t
    _cond: lock_less_condition = field(default_factory=lock_less_condition)

    async def _wait_until(self, predicate: Callable[[observable_data_t], bool]) -> None:
        # When using this function,
        # make sure that `predicate` depends only on passed value.
        # Otherwise might get a deadlock, because
        # you would not be notified when other values change.
        while not predicate(self._value):
            await self._cond.wait()

    def __enter__(self) -> observable_data_t:
        return self._value
    
    def __exit__(self, *_: Any) -> None:
        self._cond.notify()

@dataclass
class RecvBuffer:
    size: int

    _data: observable_data[dict[int, bytes]] = field(default_factory=lambda: observable_data(dict()))
    _consumed = 0

    def __post_init__(self) -> None:
        if self.size <= 0:
            raise ValueError("size must be positive")

    def recv_if_can(self, index: int, data: bytes) -> bool:
        if index in range(self._consumed, self._consumed + self.size):
            with self._data as d:
                d.setdefault(index, data)
            return True
        else:
            # Send ACK to old messages to remove them from sender retransmission loop.
            return index < self._consumed

    async def read(self) -> bytes:
        while True:
            await self._data._wait_until(lambda d: self._consumed in d)
            with self._data as d:
                value = d.pop(self._consumed)
                self._consumed += 1
                return value

@dataclass
class SendBuffer:
    size: int

    _data: observable_data[dict[int, bytes]] = field(default_factory=lambda: observable_data(dict()))
    _externally_written: int = 0
    _message_selector: AsyncGenerator[tuple[int, bytes], None] = cast(AsyncGenerator[tuple[int, bytes], None], ...)

    def __post_init__(self) -> None:
        if self.size <= 0:
            raise ValueError("size must be positive")
        self._message_selector = self.__message_selector()

    async def __message_selector(self) -> AsyncGenerator[tuple[int, bytes], None]:
        while True:
            await self._data._wait_until(lambda d: bool(d))
            with self._data as d:
                min_d_keys = min(d.keys())
            for index in range(min_d_keys, self._externally_written):
                with self._data as d:
                    value = d.get(index, None)
                if value is not None:
                    yield index, value

    async def write(self, data: bytes) -> None:
        await self._data._wait_until(lambda d: len(d) < self.size)

        with self._data as d:

            index = self._externally_written
            self._externally_written += 1

            d[index] = data
            return

    def mark_as_delivered(self, index: int) -> None:
        with self._data as d:
            d.pop(index, None)

    async def select_message_to_send(self) -> tuple[int, bytes]:
        return await self._message_selector.asend(None)

class ITransport(abc.ABC):
    # part of public interface

    @abc.abstractmethod
    async def read(self) -> bytes:
        ...

    @abc.abstractmethod
    async def write(self, data: bytes) -> None:
        ...

@dataclass
class _RetryTransport(ITransport):
    conf: Config

    _send_buffer: SendBuffer = cast(SendBuffer, ...)
    _recv_buffer: RecvBuffer = cast(RecvBuffer, ...)
    _loop_started: bool = False
    _wrapped: _DeliveryMessagesTransport = cast(_DeliveryMessagesTransport, ...)
    _acks_to_send: asyncio.Queue[int] = field(default_factory=asyncio.Queue)

    def __post_init__(self) -> None:
        self._send_buffer = SendBuffer(self.conf.cache_chunks)
        self._recv_buffer = RecvBuffer(self.conf.cache_chunks)
        self._wrapped = _DeliveryMessagesTransport(
            self.conf,
            self.__on_recv_data,
            self.__on_recv_ack,
        )

    def __on_recv_data(self, index: int, data: bytes) -> None:
        if self._recv_buffer.recv_if_can(index, data):
            self._acks_to_send.put_nowait(index)

    def __on_recv_ack(self, index: int) -> None:
        self._send_buffer.mark_as_delivered(index)

    async def no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        self.__loop_starter()
        return await self._wrapped.no_owning_run(reader, writer)

    async def read(self) -> bytes:
        self.__loop_starter()
        return await self._recv_buffer.read()

    async def write(self, data: bytes) -> None:
        self.__loop_starter()
        await self._send_buffer.write(data)

    def __loop_starter(self) -> None:
        if not self._loop_started and can_use_event_loop():
            # Exceptions that happen in streams of this transport
            # should be propagated to callers of `no_owning_run()`.
            # If any exception is propagated here and not to caller of `no_owning_run()`,
            # then it is an error and we should halt.
            self._loop_started = True
            fire(self.__loop(), halt_on_exception=True)

    async def __loop(self) -> None:
        await gather_and_cancel(
            self.__internal_send_loop(),
            self.__ack_send_loop(),
        )

    async def __ack_send_loop(self) -> None:
        while True:
            acks_to_send = {await self._acks_to_send.get()}
            while not self._acks_to_send.empty():
                acks_to_send.add(self._acks_to_send.get_nowait())
            for index in acks_to_send:
                try:
                    await self._wrapped.write_ack(index)
                except Exception as e:
                    # Failure to send ACK can be ignored
                    # Make asyncio print stack to console
                    fire(async_raise(e), halt_on_exception=False)

    async def __internal_send_loop(self) -> None:
        while True:
            index, data = await self._send_buffer.select_message_to_send()
            await self._wrapped.write_data(index, data)

@dataclass
class _DebuggerTransport(ITransport):
    # Temporary wrapper to debug implementation.
    # Intention to catch reorderings and broken packets.
    # No intention of cryptographic security.
    # This class might be removed in production.

    conf: Config

    _wrapped: _RetryTransport = cast(_RetryTransport, ...)
    _send_count: int = 0
    _recv_count: int = 0

    def __post_init__(self) -> None:
        self._wrapped = _RetryTransport(self.conf)

    async def no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        return await self._wrapped.no_owning_run(reader, writer)

    async def read(self) -> bytes:
        data = await self._wrapped.read()
        if len(data) < 12:
            terminate(f"received {data = !r}")
        good_checksum, data = int.from_bytes(data[0:4], 'big'), data[4:]
        have_checksum = zlib.adler32(data)
        if good_checksum != have_checksum:
            terminate(f"Checksum failure: {have_checksum = }, {good_checksum = }")
        index, data = int.from_bytes(data[0:8], 'big'), data[8:]
        if index != self._recv_count:
            terminate(f"Wrong index received: {index = }, {self._recv_count = }")
        self._recv_count += 1
        return data

    async def write(self, data: bytes) -> None:
        data = self._send_count.to_bytes(8, 'big') + data
        data = zlib.adler32(data).to_bytes(4, 'big') + data
        self._send_count += 1
        await self._wrapped.write(data)

@dataclass
class AcceptedTransports:
    # part of public interface
    conf: Config
    on_new_transport: Callable[[ITransport], object]

    _accepted_transports: dict[uuid.UUID, _DebuggerTransport] = field(default_factory=dict)

    async def no_owning_accept(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # part of public interface
        transport_id = uuid.UUID(bytes=await reader.readexactly(uuid_bytes_size))
        writer.write(transport_id.bytes)
        await writer.drain()
        if transport_id not in self._accepted_transports:
            self._accepted_transports[transport_id] = _DebuggerTransport(self.conf)
            asyncio.get_running_loop().call_soon(
                partial(
                    self.on_new_transport,
                    self._accepted_transports[transport_id]
                )
            )
        await self._accepted_transports[transport_id].no_owning_run(reader, writer)

@dataclass
class ConnectedTransports:
    # part of public interface
    conf: Config
    transport_id: uuid.UUID = field(default_factory=uuid.uuid4)
    wrapped: _DebuggerTransport = cast(_DebuggerTransport, ...)

    def __post_init__(self) -> None:
        self.wrapped = _DebuggerTransport(self.conf)

    async def no_owning_connect(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # part of public interface
        writer.write(self.transport_id.bytes)
        await writer.drain()
        transport_id = uuid.UUID(bytes=await reader.readexactly(len(self.transport_id.bytes)))
        if self.transport_id != transport_id:
            raise ValueError(f"Server {transport_id = } is not expected {self.transport_id = }")
        await self.wrapped.no_owning_run(reader, writer)

