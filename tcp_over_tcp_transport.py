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
import heapq

############################################################################################################################

from tcp_over_tcp_useful_tools import terminate, wait_until_all_complete_or_cancel_on_exc, can_use_event_loop, fire, uuid_bytes_size

############################################################################################################################

# This file is not a security layer.
# Authentication and encryption must be handled on other layers.

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

@dataclass(frozen=True, kw_only=True)
class Config:
    alive_interval: float = 15
    max_missing_alives: int = 1
    cache_chunks: int = 256
    max_chunk_size: int = 2**40
    resend_interval: float = 8
    disable_encryption: bool = False
    disable_authentication: bool = False

    def __post_init__(self) -> None:
        if self.alive_interval <= 0:
            raise ValueError("alive_interval must be > 0")
        if self.max_missing_alives < 0:
            raise ValueError("wait_until_all_complete_or_cancel_on_exc must be >= 0")
        if self.cache_chunks <= 0:
            raise ValueError("cache_chunks must be > 0")
        if self.max_chunk_size <= 0:
            raise ValueError("max_chunk_size must be > 0")
        if self.max_chunk_size >= 2**64-1:
            raise ValueError("max_chunk_size must be < 2**64-1")
        if self.resend_interval <= 0:
            raise ValueError("resend_interval must be > 0")
        if not self.disable_encryption:
            raise ValueError("Encryption is not supported.")
        if not self.disable_authentication:
            raise ValueError("Authentication is not supported.")

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
            # We join size to data into single blob
            # because `wrapped.write()` does not guarantee that
            # multiple calls arrive in same order.
            # But it guarantees that passed blob
            # is treated as a whole object,
            # so in would not be split,
            # and on other side we can expect (size and data),
            # not (size, keep alive, data).
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
    __alive_queue: asyncio.Queue[None] = cast(asyncio.Queue[None], ...)

    def __post_init__(self) -> None:
        self.__alive_queue: asyncio.Queue[None] = asyncio.Queue(maxsize=self.conf.max_missing_alives*2+8)

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
            self.__last_alive = time.monotonic()
            if data is not None:
                self.on_recv(data)
                continue

    async def __check_loop(self) -> None:
        while True:
            current_time = time.monotonic()
            max_delay_since_last_alive = self.conf.alive_interval * ( self.conf.max_missing_alives + 1 )
            until_timeout = self.__last_alive + max_delay_since_last_alive - current_time
            if until_timeout <= 0:
                raise RuntimeError(f"Timeout: No keepalive signals for {current_time - self.__last_alive} seconds.")
            await asyncio.sleep(until_timeout)

    async def loop(self) -> None:
        await wait_until_all_complete_or_cancel_on_exc(
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
        # This function is allowed to be called in parallel by different streams.
        # Different messages intentionally can be sent via different `wrapped`s.
        # This class does not guarantee delivery or order.
        return await self._wrapped.no_owning_run(reader, writer)

@dataclass
class lock_less_condition:
    # Not thread safe.
    # Requires event loop to be cooperative.

    _fut: asyncio.Future[None] | None = None

    def notify_all(self) -> None:
        if self._fut is not None:
            fut = self._fut
            self._fut = None
            fut.set_result(None)

    async def wait_until(self, predicate: Callable[[], bool]) -> None:
        while not predicate():
            if self._fut is None:
                self._fut = asyncio.Future()
            await self._fut

@dataclass
class SendBuffer:
    size: int
    resend_interval: float
    on_send: Callable[[int, bytes], Awaitable[Any]]

    _data: dict[int, bytes] = field(default_factory=dict)
    _externally_written: int = 0
    _cond: lock_less_condition = field(default_factory=lock_less_condition)
    _heap: list[tuple[float, int]] = field(default_factory=list)

    def __post_init__(self) -> None:
        if self.size <= 0:
            raise ValueError("size must be positive")

    async def __heap_notifier(self) -> None:
        while True:
            await self._cond.wait_until(lambda: bool(self._heap))
            await asyncio.sleep(self._heap[0][0] - time.monotonic())
            self._cond.notify_all()

    async def __select_message_to_send(self) -> None:
        while True:
            await self._cond.wait_until(lambda: bool(self._heap and self._heap[0][0] <= time.monotonic()))
            
            send_at, index = heapq.heappop(self._heap)
            self._cond.notify_all()

            if index not in self._data:
                continue

            data = self._data[index]
            logging.debug(F"Chunk {index:20d}: sending to transport")
            await self.on_send(index, data)

            heapq.heappush(self._heap, (time.monotonic() + self.resend_interval, index))
            self._cond.notify_all()

    async def loop(self) -> None:
        await wait_until_all_complete_or_cancel_on_exc(
            self.__heap_notifier(),
            self.__select_message_to_send(),
        )

    async def write(self, data: bytes) -> None:
        await self._cond.wait_until(lambda: len(self._data) < self.size)

        index = self._externally_written
        self._externally_written += 1

        heapq.heappush(self._heap, (time.monotonic(), index))
        self._data[index] = data

        logging.debug(F"Chunk {index:20d}: written to send buffer")
        self._cond.notify_all()

    def mark_as_delivered(self, index: int) -> None:
        logging.debug(F"Chunk {index:20d}: received ACK")
        self._data.pop(index, None)
        self._cond.notify_all()

@dataclass
class RecvBuffer:
    size: int

    _cond: lock_less_condition = field(default_factory=lock_less_condition)
    _data: dict[int, bytes] = field(default_factory=dict)
    _consumed = 0

    def __post_init__(self) -> None:
        if self.size <= 0:
            raise ValueError("size must be positive")

    def recv_if_can(self, index: int, data: bytes) -> bool:
        if index in range(self._consumed, self._consumed + self.size):
            if index in self._data:
                logging.debug(F"Chunk {index:20d}: recv duplicate")
            else:
                logging.debug(F"Chunk {index:20d}: recv first")
                self._data[index] = data
                self._cond.notify_all()
            return True
        else:
            if index < self._consumed:
                logging.debug(F"Chunk {index:20d}: too old")
                # Send ACK to old messages to remove them from sender retransmission loop.
                return True
            else:
                logging.debug(F"Chunk {index:20d}: too new")
                return False


    async def read(self) -> bytes:
        while True:
            await self._cond.wait_until(lambda: self._consumed in self._data)
            value = self._data.pop(self._consumed)
            self._cond.notify_all()
            logging.debug(F"Chunk {self._consumed:20d}: consumed")
            self._consumed += 1
            return value

class ITransport(abc.ABC):
    # part of public interface

    @abc.abstractmethod
    async def read(self) -> bytes:
        ...

    @abc.abstractmethod
    async def write(self, data: bytes) -> None:
        ...

    @abc.abstractmethod
    async def _no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
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
        self._wrapped = _DeliveryMessagesTransport(
            self.conf,
            self.__on_recv_data,
            self.__on_recv_ack,
        )
        self._send_buffer = SendBuffer(
            self.conf.cache_chunks,
            self.conf.resend_interval,
            self._wrapped.write_data,
        )
        self._recv_buffer = RecvBuffer(self.conf.cache_chunks)

    def __on_recv_data(self, index: int, data: bytes) -> None:
        if self._recv_buffer.recv_if_can(index, data):
            self._acks_to_send.put_nowait(index)

    def __on_recv_ack(self, index: int) -> None:
        self._send_buffer.mark_as_delivered(index)

    async def _no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # This function is allowed to be called in parallel by different streams.
        # Different messages intentionally can be sent via different `wrapped`s.
        # This class guarantees delivery and order.
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
        await wait_until_all_complete_or_cancel_on_exc(
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
                    logging.warning(f"Sending ACK error: {e!r}")

    async def __internal_send_loop(self) -> None:
        await self._send_buffer.loop()

@dataclass
class _DebuggerTransport(ITransport):
    # Intention to catch reorderings and broken packets.
    # No intention of cryptographic security.

    conf: Config

    _wrapped: _RetryTransport = cast(_RetryTransport, ...)
    _send_count: int = 0
    _recv_count: int = 0

    def __post_init__(self) -> None:
        self._wrapped = _RetryTransport(self.conf)

    async def _no_owning_run(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # This function is allowed to be called in parallel by different streams.
        return await self._wrapped._no_owning_run(reader, writer)

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

    _accepted_transports: dict[uuid.UUID, ITransport] = field(default_factory=dict)

    async def no_owning_accept(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # part of public interface
        # This function is allowed to be called in parallel by different streams.
        # This UUID is not for authentication.
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
        await self._accepted_transports[transport_id]._no_owning_run(reader, writer)

@dataclass
class ConnectedTransports:
    # part of public interface
    conf: Config
    transport_id: uuid.UUID = field(default_factory=uuid.uuid4)
    wrapped: ITransport = cast(ITransport, ...)

    def __post_init__(self) -> None:
        self.wrapped = _DebuggerTransport(self.conf)

    async def no_owning_connect(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        # part of public interface
        # This function is allowed to be called in parallel by different streams.
        writer.write(self.transport_id.bytes)
        await writer.drain()
        transport_id = uuid.UUID(bytes=await reader.readexactly(len(self.transport_id.bytes)))
        if self.transport_id != transport_id:
            raise ValueError(f"Server {transport_id = } is not expected {self.transport_id = }")
        await self.wrapped._no_owning_run(reader, writer)

