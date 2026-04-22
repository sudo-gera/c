from __future__ import annotations
from collections import *
from dataclasses import *
from functools import *
from itertools import *
from operator import *
from typing import *
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


############################################################################################################################

if sys.version_info >= (3, 10) and TYPE_CHECKING:
    from _typeshed import DataclassInstance
else:
    DataclassInstance = Any

if sys.version_info < (3, 10):
    def call(obj: Any, /, *args: Any, **kwargs: Any) -> Any:
        return obj(*args, **kwargs)

elif sys.version_info < (3, 11):
    from collections.abc import Callable as caCallable
    call_R = TypeVar("call_R")
    call_P = ParamSpec("call_P")
    def call(obj: caCallable[call_P, call_R], /, *args: call_P.args, **kwargs: call_P.kwargs) -> call_R:
        return obj(*args, **kwargs)

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

############################################################################################################################

logger = logging.getLogger(__name__)

class always_upper_str(str):
    def __new__(cls, *args: Any, **kwargs: Any) -> always_upper_str:
        return super().__new__(cls,
            super().__new__(cls, *args, **kwargs).upper()
        )

logging_levels = [name for name in dir(logging) if isinstance(logging.getLevelName(name), int)]

logging_levels_case_insensitive = [always_upper_str(a) for a in logging_levels]

############################################################################################################################

def isinstance_typing(value: Any, t: Any) -> bool:
    try:
        return isinstance(value, t)
    except TypeError:
        pass

    origin = typing.get_origin(t)
    args = typing.get_args(t)
    assert origin is not None

    if origin is Literal:
        assert len(args) == 1
        return bool(value == args[0])

    if not isinstance_typing(value, origin):
        return False

    if origin is list:
        assert len(args) == 1
        return all([
            isinstance_typing(v, args[0])
            for v in value
        ])

    if origin is str:
        assert len(args) == 1
        return all([
            isinstance_typing(v, args[0])
            for v in value
        ])

    if origin is dict:
        assert len(args) == 2
        return all([
            isinstance_typing(k, args[0]) and isinstance_typing(v, args[1])
            for k, v in value.items()
        ])

    if origin is tuple:
        if len(args) == 2 and args[1] is ...:
            return all([
                isinstance_typing(v, args[0])
                for v in value
            ])
        else:
            if len(args) != len(value):
                return False
            return all([
                isinstance_typing(v, t)
                for v, t in zip(value, args)
            ])

    assert False

############################################################################################################################

@dataclass(frozen=True)
class dataclass_field:
    field: Field[Any]
    type: Any

@cache
def get_fields(dclass: DataclassInstance) -> list[dataclass_field]:

    def process_one_filed(field: Field[Any]) -> dataclass_field:
        if isinstance(field.type, str):
            field_type = eval(field.type)
        else:
            field_type = field.type
        return dataclass_field(
            field=field,
            type=field_type,
        )

    return [
        process_one_filed(field)
        for field in fields(dclass)
    ]

def check_dataclass_types(data: DataclassInstance) -> None:

    for field in get_fields(type(data)):
        assert isinstance_typing(getattr(data, field.field.name), field.type)

dict_to_dataclass_t = TypeVar('dict_to_dataclass_t', bound=DataclassInstance)

def dict_to_dataclass(data: dict[str, Any], dclass_type: type[dict_to_dataclass_t]) -> dict_to_dataclass_t:

    assert all([isinstance(k, str) for k in data])
    result = dclass_type(**data)
    check_dataclass_types(result)
    return result

############################################################################################################################

def setup_parser_from_dataclass(parser: argparse.ArgumentParser, args_dataclass: type[DataclassInstance]) -> None:
    for field in get_fields(args_dataclass):

        arg_name = field.field.name
        arg_required = True
        arg_type : type[Any]|None = None
        arg_default : Any = None

        if field.field.default is not MISSING: # v: t = SOME_DEFAULT
            arg_default = field.field.default
            arg_required = False

        if field.field.default_factory is not MISSING: # v: t = field(default_factory=SOME_CALLABLE)
            arg_default = field.field.default_factory()
            arg_required = False

        if isinstance(field.type, type): # v: t and t is type not union
            arg_type = field.type

        if (
            sys.version_info >= (3, 10)
            and
            isinstance(field.type, types.UnionType)  # t | None
            or
            typing.get_origin(field.type) is typing.Union  # typing.Optional[t], typing.Union[t, None], typing.Union[t, type(None)]
        ):
            union_args = typing.get_args(field.type)
            assert len(union_args) == 2
            assert not arg_required # has some default value
            assert arg_default is None
            assert type(arg_default) in union_args
            non_default_type = union_args[union_args[0] == type(arg_default)]
            assert isinstance(non_default_type, type)
            assert non_default_type is type(None)
            assert arg_type is None
            arg_type = non_default_type

        assert arg_type is not None

        parser.add_argument(
            '--' + arg_name.replace('_', '-'),
            required=arg_required,
            type=arg_type,
            default=arg_default,
        )


############################################################################################################################

def dataclass_to_json(value: DataclassInstance) -> str:
    check_dataclass_types(value)
    return json.dumps(vars(value), indent=4)

json_to_dataclass_t = TypeVar('json_to_dataclass_t', bound=DataclassInstance)

def json_to_dataclass(data: str, dclass_type: type[json_to_dataclass_t]) -> json_to_dataclass_t:
    d = json.loads(data)
    assert isinstance(d, dict)
    assert all([isinstance(k, str) for k in d])
    return dict_to_dataclass(d, dclass_type)

############################################################################################################################

def dataclass_to_file(value: DataclassInstance, path: pathlib.Path) -> None:
    data = dataclass_to_json(value)
    with path.open('w') as file:
        file.write(data)

file_to_dataclass_t = TypeVar('file_to_dataclass_t', bound=DataclassInstance)

def file_to_dataclass(path: pathlib.Path, dclass_type: type[file_to_dataclass_t]) -> file_to_dataclass_t:
    if not path.exists():
        with path.open('w') as file:
            json.dump({}, file)
    assert path.exists()
    assert path.is_file()
    with path.open('r') as file:
        data = file.read()
    return json_to_dataclass(data, dclass_type)

############################################################################################################################

class path_based_lock:
    def __init__(self, path: pathlib.Path, force_new_lock: bool):
        assert force_new_lock
        self.__path = path
        self.__is_locked = False
        self.__update_future : asyncio.Future[None] | None = None

    def checking_switch_to(self, new_val: bool) -> None:
        assert self.__is_locked != new_val
        self.__is_locked = new_val
        if self.__update_future is not None:
            self.__update_future.set_result(None)
            self.__update_future = None

    async def wait_for_update(self) -> None:
        if self.__update_future is None:
            self.__update_future = asyncio.Future()
        await self.__update_future

    def is_locked(self) -> bool:
        return self.__is_locked

@cache
def get_path_based_lock(path: pathlib.Path) -> path_based_lock:
    rpath = path.resolve()
    if rpath != path:
        return get_path_based_lock(rpath)
    return path_based_lock(path, force_new_lock=True)

############################################################################################################################

mutexted_file_t = TypeVar('mutexted_file_t', bound=DataclassInstance)

class locked_dataclass_file(typing.Generic[mutexted_file_t]):

    def __init__(self, path: pathlib.Path, dclass_type: type[mutexted_file_t]) -> None:
        self.__path = path
        self.__dclass_type = dclass_type
        self.__lock = get_path_based_lock(path)
        self.__db : mutexted_file_t | None = None

    def __enter__(self) -> mutexted_file_t:
        self.__lock.checking_switch_to(True)
        self.__db = file_to_dataclass(self.__path, self.__dclass_type)
        return self.__db

    def __exit__(self, exc_type: type[Any] | None, exc_value: Any, traceback: Any) -> None:
        try:
            if exc_type is None:
                assert self.__db is not None
                dataclass_to_file(self.__db, self.__path)
        finally:
            self.__db = None
            self.__lock.checking_switch_to(False)

    async def __aenter__(self) -> mutexted_file_t:
        while self.__lock.is_locked():
            await self.__lock.wait_for_update()
        return self.__enter__()

    async def __aexit__(self, exc_type: type[Any] | None, exc_value: Any, traceback: Any) -> None:
        return self.__exit__(exc_type, exc_value, traceback)

############################################################################################################################

class alive_or_raise:

    def __init__(self) -> None:
        self.mark_as_alive()
        self.started = False

    def mark_as_alive(self) -> None:
        if not self.started:
            fire(self.checker())
            self.started = True
        self.__last_alive_mark = time.time()

    async def checker(self) -> None:
        while 1:
            await asyncio.sleep(1)
            ct = time.time()
            if ct - self.__last_alive_mark > 60:
                raise KeyboardInterrupt

alive = alive_or_raise()

############################################################################################################################

subparsers_as_dataclass_handler_type = TypeVar('subparsers_as_dataclass_handler_type')

@dataclass(frozen=True)
class subparsers_as_dataclass_parser_ctx(Generic[subparsers_as_dataclass_handler_type]):
    dataclass: type[DataclassInstance]
    handler: subparsers_as_dataclass_handler_type

class subparsers_as_dataclass(Generic[subparsers_as_dataclass_handler_type]):

    def __init__(self, subparsers : argparse._SubParsersAction[argparse.ArgumentParser]):
        self.subparsers = subparsers
        self.dataclasses : dict[str, subparsers_as_dataclass_parser_ctx[subparsers_as_dataclass_handler_type]] = {}

    def add_subparser_from_dataclass(self, parser_name: str, args_dataclass: type[DataclassInstance], handler: subparsers_as_dataclass_handler_type) -> None:
        parser = self.subparsers.add_parser(parser_name)
        setup_parser_from_dataclass(parser, args_dataclass)
        assert parser_name not in self.dataclasses
        self.dataclasses[parser_name] = subparsers_as_dataclass_parser_ctx(
            args_dataclass,
            handler,
        )

    def get_handler(self, args: argparse.Namespace) -> tuple[subparsers_as_dataclass_handler_type, DataclassInstance]:
        ctx = self.dataclasses[vars(args)[self.subparsers.dest]]
        dataclass_attrs = {field.field.name for field in get_fields(ctx.dataclass)}
        return ctx.handler, ctx.dataclass(**{k:v for k,v in vars(args).items() if k in dataclass_attrs})

############################################################################################################################

class print_count_on_exit:
    def __init__(self, name: str) -> None:
        self.value = 0
        self.name = name

    def add(self, value: int) -> None:
        self.value += value

    def __del__(self, *a: Any) -> None:
        print(self.name, self.value)

############################################################################################################################

tcp_bytes_send_count = print_count_on_exit('tcp_bytes_send_count')
tcp_bytes_recv_count = print_count_on_exit('tcp_bytes_recv_count')

reader_from_stream_reader_signature = Callable[[asyncio.StreamReader], Awaitable[Any]]

readers_from_stream_reader : dict[type[Any], reader_from_stream_reader_signature] = {}

@dataclass(frozen=True)
class reads_from_stream_reader:
    type_to_read: type[Any]

    def __call__(self, func: reader_from_stream_reader_signature) -> reader_from_stream_reader_signature:
        readers_from_stream_reader[self.type_to_read] = func
        return func

read_from_stream_reader_type = TypeVar('read_from_stream_reader_type')

async def read_from_stream_reader(reader: asyncio.StreamReader, type_to_read: type[read_from_stream_reader_type]) -> read_from_stream_reader_type:
    value = await readers_from_stream_reader[type_to_read](reader)
    assert isinstance(value, type_to_read)
    return value

writer_to_stream_writer_signature = Callable[[asyncio.StreamWriter, Any], Awaitable[None]]

writers_to_stream_writer : dict[type[Any], writer_to_stream_writer_signature] = {}

@dataclass(frozen=True)
class writes_to_stream_writer:
    type_to_write: type[Any]

    def __call__(self, func: writer_to_stream_writer_signature) -> writer_to_stream_writer_signature:
        writers_to_stream_writer[self.type_to_write] = func
        return func

write_to_stream_writer_ongoing_requests = 0

async def write_to_stream_writer(writer: asyncio.StreamWriter, value: Any) -> None:
    await writers_to_stream_writer[type(value)](writer, value)

inherit_stream_reader_and_writer_new_type = TypeVar('inherit_stream_reader_and_writer_new_type')
inherit_stream_reader_and_writer_old_type = TypeVar('inherit_stream_reader_and_writer_old_type')
def inherit_stream_reader_and_writer(
    new_type: type[inherit_stream_reader_and_writer_new_type],
    old_type: type[inherit_stream_reader_and_writer_old_type],
    converter_from_old_to_new: Callable[[inherit_stream_reader_and_writer_old_type], inherit_stream_reader_and_writer_new_type],
    converter_from_new_to_old: Callable[[inherit_stream_reader_and_writer_new_type], inherit_stream_reader_and_writer_old_type],
) -> None:
    @reads_from_stream_reader(new_type)
    async def read_something_from_stream_reader(reader: asyncio.StreamReader) -> inherit_stream_reader_and_writer_new_type:
        value = await read_from_stream_reader(reader, old_type)
        return converter_from_old_to_new(value)

    @writes_to_stream_writer(new_type)
    async def write_something_to_stream_writer(writer: asyncio.StreamWriter, value: inherit_stream_reader_and_writer_new_type) -> None:
        await write_to_stream_writer(writer, converter_from_new_to_old(value))

def setup_reader_and_writer_for_dataclass(cls: type[DataclassInstance]) -> None:

    @reads_from_stream_reader(cls)
    async def read_something_from_stream_reader(reader: asyncio.StreamReader) -> Any:

        async def read_one_field(field: dataclass_field) -> Any:
            value: Any = await read_from_stream_reader(reader, field.type)
            return value

        return cls(
            **{
                field.field.name: await read_one_field(field)
                for field in get_fields(cls)
            }
        )

    @writes_to_stream_writer(cls)
    async def write_something_to_stream_writer(writer: asyncio.StreamWriter, value: Any) -> None:
        for field in get_fields(cls):
            field_value = getattr(value, field.field.name)
            assert type(field_value) == field.type
            await write_to_stream_writer(writer, field_value)

@call
def setup_default_types() -> None:
    # bytes

    @reads_from_stream_reader(bytes)
    async def read_bytes_from_stream_reader(reader: asyncio.StreamReader) -> bytes:
        data_len = int.from_bytes(await reader.readexactly(8), 'little')
        value = await reader.readexactly(data_len)
        # tcp_bytes_recv_count.add(8 + len(value))
        return value

    @writes_to_stream_writer(bytes)
    async def write_bytes_to_stream_writer(writer: asyncio.StreamWriter, value: bytes) -> None:
        # tcp_bytes_send_count.add(8 + len(value))
        writer.write(len(value).to_bytes(8, 'little'))
        writer.write(value)
        # await writer.drain()

    # bytearray

    inherit_stream_reader_and_writer(bytearray, bytes, bytearray, bytes)

    # str

    inherit_stream_reader_and_writer(str, bytes, methodcaller('decode'), methodcaller('encode'))

    # int

    inherit_stream_reader_and_writer(int, str, int, str)

    # fractions.Fraction

    inherit_stream_reader_and_writer(fractions.Fraction, str, fractions.Fraction, str)

    # float

    inherit_stream_reader_and_writer(float, fractions.Fraction, float, fractions.Fraction)

    # UUID

    inherit_stream_reader_and_writer(uuid.UUID, str, uuid.UUID, str)

############################################################################################################################

class MemoryTransport(asyncio.Transport):
    _extra: Dict[str, Any]
    _protocol: asyncio.protocols.Protocol
    _closed: bool
    _write_buffer_size: int

    def __init__(self, protocol: asyncio.protocols.Protocol, *, extra: Optional[Dict[str, Any]] = None) -> None:
        super().__init__()
        self._protocol = protocol
        self._extra = extra or {}
        self._closed = False
        self._write_buffer_size = 0

    # ----- Transport API -------------------------------------------------

    def get_extra_info(self, name: str, default: Any = None) -> Any:
        return self._extra.get(name, default)

    def write(self, data: bytes | bytearray | memoryview) -> None:
        if self._closed:
            raise RuntimeError("Transport is closed")

        self._write_buffer_size += len(data)
        loop = asyncio.get_running_loop()
        # Schedule delivery to mimic real async transports
        loop.call_soon(self._deliver, data)

    def _deliver(self, data: bytes | bytearray | memoryview) -> None:
        try:
            self._protocol.data_received(bytes(data))
        finally:
            self._write_buffer_size -= len(data)

    def close(self) -> None:
        if self._closed:
            return
        self._closed = True

        loop = asyncio.get_running_loop()
        loop.call_soon(self._protocol.eof_received)
        loop.call_soon(self._protocol.connection_lost, None)

    def is_closing(self) -> bool:
        return self._closed

    def can_write_eof(self) -> bool:
        return False

    def abort(self) -> None:
        if self._closed:
            return
        self._closed = True
        loop = asyncio.get_running_loop()
        loop.call_soon(self._protocol.connection_lost, RuntimeError("aborted"))

    # Optional but helps mypy for StreamWriter
    def get_write_buffer_size(self) -> int:
        return self._write_buffer_size

    def set_write_buffer_limits(self, high: Optional[int] = None, low: Optional[int] = None) -> None:
        # No backpressure in memory version
        return


async def create_in_memory_stream(
    extra_info: Optional[Dict[str, Any]] = None,
) -> tuple[asyncio.StreamReader, asyncio.StreamWriter]:
    """
    Create a pure in-memory pair compatible with StreamReader/StreamWriter.
    Fully mypy-checked.
    """

    loop: asyncio.AbstractEventLoop = asyncio.get_running_loop()
    reader: asyncio.StreamReader = asyncio.StreamReader()
    protocol: asyncio.StreamReaderProtocol = asyncio.StreamReaderProtocol(reader)

    transport: MemoryTransport = MemoryTransport(protocol, extra=extra_info)
    protocol.connection_made(transport)

    writer: asyncio.StreamWriter = asyncio.StreamWriter(transport, protocol, reader, loop)
    return reader, writer

############################################################################################################################

@call
def reader_and_writer_test() -> None:
    async def main() -> None:
        reader, writer = await create_in_memory_stream()

        for value in [b'123\x00123\n123', bytearray(b'123\x00123\n123'), 'œ', 0, 1, -1, 0.1+0.2]:
            await write_to_stream_writer(writer, value)
            assert value == await read_from_stream_reader(reader, type(value))

        writer.close()
        await writer.wait_closed()
        assert not await reader.read()

    asyncio.run(main())

############################################################################################################################

import pickle

async def write_large_chunk_to_stream_writer(writer: asyncio.StreamWriter, value: Any) -> None:
    data = pickle.dumps(value)
    assert isinstance(data, bytes)
    await write_to_stream_writer(writer, data)
    await writer.drain()

read_large_chunk_from_stream_reader_type_to_read = TypeVar('read_large_chunk_from_stream_reader_type_to_read')

async def read_large_chunk_from_stream_reader(reader: asyncio.StreamReader, type_to_read: type[read_large_chunk_from_stream_reader_type_to_read]) -> read_large_chunk_from_stream_reader_type_to_read:
    data = await read_from_stream_reader(reader, bytes)
    return cast(read_large_chunk_from_stream_reader_type_to_read, pickle.loads(data))

############################################################################################################################

put_rotate_type = TypeVar('put_rotate_type')

def put_rotate(q: asyncio.Queue[put_rotate_type], v: put_rotate_type) -> None:
    if q.full():
        q.get_nowait()
    q.put_nowait(v)

get_all_type = TypeVar('get_all_type')

async def get_all(q: asyncio.Queue[get_all_type]) -> list[get_all_type]:
    item = await q.get()
    result = [item] * (q.qsize() + 1)
    for i in range(q.qsize()):
        result[i+1] = q.get_nowait()
    return result

############################################################################################################################

async def resolve_domain(domain: str) -> list[str]:
    loop = asyncio.get_event_loop()

    addrinfo = await loop.run_in_executor(
        None,
        lambda: socket.getaddrinfo(domain, None, proto=socket.IPPROTO_TCP)
    )

    result : set[str] = set()

    for info in addrinfo:
        ip = info[4][0]
        assert isinstance(ip, str)
        result.add(ip)

    return list(result)

############################################################################################################################

def is_ip(host: str) -> bool:
    try:
        ipaddress.ip_address(host)
        return True
    except ValueError:
        return False

############################################################################################################################

uuid_bytes_len: Final = len(uuid.uuid4().bytes)

############################################################################################################################

async def event_loop_checker() -> None:
    ct = time.monotonic()
    while 1:
        pt = ct
        ct = time.monotonic()

        was_sleeping = ct - pt
        if was_sleeping > 2:
            logger.warning('The event loop was blocked for %.3f seconds.', was_sleeping)

        await asyncio.sleep(1)

############################################################################################################################

@dataclass(frozen=True)
class connection_info:
    src_host: str
    src_port: int
    dst_host: str
    dst_port: int
    connection_id: uuid.UUID
    client_id: uuid.UUID

    def __post_init__(self) -> None:
        assert len(self.src_host.encode()) < 256
        assert len(self.dst_host.encode()) < 256
        assert self.src_port in range(2**16)
        assert self.dst_port in range(2**16)
        assert len(self.client_id.bytes) == uuid_bytes_len
        assert len(self.connection_id.bytes) == uuid_bytes_len

    def reverse(self) -> connection_info:
        return replace(
            self,
            src_host=self.dst_host,
            src_port=self.dst_port,
            dst_host=self.src_host,
            dst_port=self.src_port,
        )

    @cached_property
    def to_bytes(self) -> bytes:
        data = (
            len(self.src_host).to_bytes(1, 'little')
            +
            len(self.dst_host).to_bytes(1, 'little')
            +
            self.src_host.encode()
            +
            self.dst_host.encode()
            +
            self.src_port.to_bytes(2, 'little')
            +
            self.dst_port.to_bytes(2, 'little')
            +
            self.client_id.bytes
            +
            self.connection_id.bytes
        )
        # print(data, len(self.src_host), len(self.dst_host))
        assert len(data) == len(self.src_host) + len(self.dst_host) + 2 + 2 + 16 + 16 + 2
        return data

    @staticmethod
    def from_bytes(data: bytes) -> connection_info:
        stream = io.BytesIO(data)
        src_host_len = int.from_bytes(stream.read(1), 'little')
        dst_host_len = int.from_bytes(stream.read(1), 'little')
        # print(data, src_host_len, dst_host_len)
        assert len(data) == src_host_len + dst_host_len + 2 + 2 + 16 + 16 + 2
        assert uuid_bytes_len == 16
        try:
            return connection_info(
                src_host=stream.read(src_host_len).decode(),
                dst_host=stream.read(dst_host_len).decode(),
                src_port=int.from_bytes(stream.read(2), 'little'),
                dst_port=int.from_bytes(stream.read(2), 'little'),
                client_id=uuid.UUID(bytes=stream.read(uuid_bytes_len)),
                connection_id=uuid.UUID(bytes=stream.read(uuid_bytes_len)),
            )
        finally:
            assert not stream.read()

# setup_reader_and_writer_for_dataclass(connection_info)

@reads_from_stream_reader(connection_info)
async def read_connection_info_from_stream_reader(reader: asyncio.StreamReader) -> connection_info:
    data = await read_from_stream_reader(reader, bytes)
    return connection_info.from_bytes(data)

@writes_to_stream_writer(connection_info)
async def write_connection_info_to_stream_writer(writer: asyncio.StreamWriter, value: connection_info) -> None:
    data = value.to_bytes
    await write_to_stream_writer(writer, data)


@dataclass(frozen=True)
class datagram:
    connection: connection_info
    data: bytes

setup_reader_and_writer_for_dataclass(datagram)

@dataclass(frozen=True)
class tcp_client_hello:
    client_id: uuid.UUID

setup_reader_and_writer_for_dataclass(tcp_client_hello)

# @dataclass(frozen=True)
# class datagram_batch:
#     items: tuple[datagram, ...]

############################################################################################################################

@dataclass(frozen=True)
class server_args:
    tcp_listen_host: str
    tcp_listen_port: int

    timeout: float

    datagram_buffer_len: int

async def server_main(args: server_args) -> None:

    alive.mark_as_alive()

    # fire(event_loop_checker())

    @dataclass(frozen=True)
    class tcp_client_context:
        client_id: uuid.UUID
        server_to_client_queue: asyncio.Queue[datagram] = field(
            default_factory=lambda: asyncio.Queue(
                maxsize=args.datagram_buffer_len
            )
        )

    tcp_client_contexts : dict[uuid.UUID, tcp_client_context] = {}

    def get_tcp_client_context(client_id: uuid.UUID) -> tcp_client_context:
        if client_id not in tcp_client_contexts:
            tcp_client_contexts[client_id] = tcp_client_context(client_id)
        return tcp_client_contexts[client_id]

    @dataclass(frozen=True)
    class udp_client_protocol(asyncio.DatagramProtocol):
        connection_server_to_client: connection_info
        transport_future: asyncio.Future[asyncio.DatagramTransport] = field(default_factory=asyncio.Future)

        last_event_time: list[float] = field(default_factory=lambda: [time.monotonic()])

        def __post_init__(self) -> None:
            fire(self.timeout_checker())

        async def timeout_checker(self) -> None:
            while 1:
                ct = time.monotonic()
                time_from_last_event = ct - self.last_event_time[0]
                time_till_closing_by_timeout = args.timeout - time_from_last_event
                if time_till_closing_by_timeout < 0:
                    logger.info('Disconnecting UDP client with connection_id = %s by timeout.', self.connection_server_to_client.connection_id)
                    transport = await self.transport_future
                    transport.abort()
                    udp_clients.pop(self.connection_server_to_client.connection_id, None)
                    break
                else:
                    await asyncio.sleep(time_till_closing_by_timeout)

        def connection_made(self, transport: asyncio.BaseTransport) -> None:

            self.last_event_time[0] = time.monotonic()

            connection_id = self.connection_server_to_client.connection_id

            logger.info('UDP client for connection_id = %s connected.', connection_id)

            self.transport_future.set_result(
                cast(
                    asyncio.DatagramTransport,
                    transport
                )
            )

        def datagram_received(self, data: bytes, weird_src_addr: tuple[str | Any, int]) -> None:

            self.last_event_time[0] = time.monotonic()

            msg = datagram(
                connection=self.connection_server_to_client,
                data=data,
            )

            logger.debug('External datagram: %d bytes from %s.', len(msg.data), msg.connection)

            client_context = get_tcp_client_context(client_id=msg.connection.client_id)

            put_rotate(client_context.server_to_client_queue, msg)

        async def send_datagram(self, msg: datagram) -> None:

            self.last_event_time[0] = time.monotonic()

            logger.debug('Internal datagram: %d bytes from %s.', len(msg.data), msg.connection)

            transport = await self.transport_future

            transport.sendto(
                data = msg.data,
            )

        def error_received(self, exc: Exception) -> None:
            logger.warning('UDP server received an error: %r.', exc)

        def connection_lost(self, exc: Exception | None) -> None:
            logger.warning('UDP server stopped with an error: %r.', exc)

    udp_clients : dict[uuid.UUID, udp_client_protocol] = {}

    async def get_udp_client(msg: datagram) -> udp_client_protocol:
        client = udp_clients.get(msg.connection.connection_id, None)

        if client is None:

            dst_hosts = [msg.connection.dst_host]

            if not is_ip(dst_hosts[0]):
                logger.debug('Resolving domain %r...', dst_hosts[0])
                dst_hosts = await resolve_domain(dst_hosts[0])
                logger.debug('Resolved into %r.', dst_hosts)

            random.shuffle(dst_hosts)

            assert dst_hosts

            for dst_host in dst_hosts:

                logger.debug('From IPs returned by DNS randomly selecting %r.', dst_host)

                msg = replace(
                    msg,
                    connection=replace(
                        msg.connection,
                        dst_host=dst_host,
                    )
                )

                loop = asyncio.get_running_loop()
                try:
                    transport, protocol = await loop.create_datagram_endpoint(
                        lambda: udp_client_protocol(
                            connection_server_to_client=msg.connection.reverse(),
                        ),
                        remote_addr=(msg.connection.dst_host, msg.connection.dst_port),
                    )
                    break
                except OSError as _exc:
                    exc = _exc
                    if exc.errno != errno.ENETUNREACH:
                        raise
            else:
                raise exc


            udp_clients[msg.connection.connection_id] = protocol

        return udp_clients[msg.connection.connection_id]

    async def on_tcp_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        with contextlib.closing(writer):
            try:

                client_hello = await read_large_chunk_from_stream_reader(reader, tcp_client_hello)

                context = get_tcp_client_context(client_hello.client_id)

                client_id = context.client_id
                logger.info('TCP client client_id = %s connected.', client_id)

                async def recv_while_can() -> None:
                    while 1:
                        msg = await read_large_chunk_from_stream_reader(reader, datagram)
                        alive.mark_as_alive()
                        udp_client = await get_udp_client(msg)
                        await udp_client.send_datagram(msg)

                async def send_while_can() -> None:
                    while 1:
                        msg = await context.server_to_client_queue.get()
                        alive.mark_as_alive()
                        await write_large_chunk_to_stream_writer(writer, msg)

                await asyncio.gather(
                    recv_while_can(),
                    send_while_can(),
                )

            except Exception as exc:
                try:
                    client_id_str = str(context.client_id)
                except Exception:
                    client_id_str = '(unknown)'
                # print(traceback.format_exc())
                logger.warning('TCP client %s stopped with an error: %r.', client_id_str, exc)

    async with await asyncio.start_server(on_tcp_connection, args.tcp_listen_host, args.tcp_listen_port) as server:
        await server.serve_forever()

############################################################################################################################

@dataclass(frozen=True)
class client_args:
    tcp_connect_host: str
    tcp_connect_port: int

    udp_listen_host: str
    udp_listen_port: int

    udp_connect_host: str
    udp_connect_port: int

    datagram_buffer_len: int

    reconnect_interval: float
    workers: int

async def client_main(args: client_args) -> None:

    alive.mark_as_alive()

    # fire(event_loop_checker())

    addr_to_id : dict[tuple[str, int], uuid.UUID] = {}

    udp_to_tcp_queue: asyncio.Queue[datagram] = asyncio.Queue(maxsize=args.datagram_buffer_len)

    client_id = uuid.uuid4()

    dst_host = args.udp_connect_host
    if not is_ip(dst_host):
        logger.debug('Domain %r will be resolved on server.', dst_host)

    dst_port = args.udp_connect_port

    @dataclass(frozen=True)
    class udp_server_protocol(asyncio.DatagramProtocol):
        transport_future: asyncio.Future[asyncio.DatagramTransport] = field(default_factory=asyncio.Future)

        def connection_made(self, transport: asyncio.BaseTransport) -> None:

            logger.info('UDP server started, assigning client_id = %s.', client_id)

            self.transport_future.set_result(
                cast(
                    asyncio.DatagramTransport,
                    transport
                )
            )

        def datagram_received(self, data: bytes, weird_src_addr: tuple[str | Any, int]) -> None:
            src_host, src_port = weird_src_addr
            assert isinstance(src_host, str)
            addr = src_host, src_port

            if addr not in addr_to_id:
                connection_id = uuid.uuid4()
                addr_to_id[addr] = connection_id
                logger.info('new UDP connection from [%s]:%d, assigning connection_id = %s.', src_host, src_port, connection_id)

            connection_id = addr_to_id[addr]

            connection = connection_info(
                src_host=src_host,
                src_port=src_port,
                dst_host=dst_host,
                dst_port=dst_port,
                connection_id=connection_id,
                client_id=client_id,
            )

            msg = datagram(
                connection=connection,
                data=data,
            )

            logger.debug('External datagram: %d bytes from %s.', len(msg.data), msg.connection)

            put_rotate(udp_to_tcp_queue, msg)

        async def send_datagram(self, msg: datagram) -> None:

            logger.debug('Internal datagram: %d bytes from %s.', len(msg.data), msg.connection)

            transport = await self.transport_future

            transport.sendto(
                data = msg.data,
                addr = (
                    msg.connection.dst_host,
                    msg.connection.dst_port,
                ),
            )

        def error_received(self, exc: Exception) -> None:
            logger.warning('UDP server received an error: %r.', exc)

        def connection_lost(self, exc: Exception | None) -> None:
            logger.warning('UDP server stopped with an error: %r.', exc)

    loop = asyncio.get_running_loop()

    transport, protocol = await loop.create_datagram_endpoint(
        udp_server_protocol,
        local_addr=(args.udp_listen_host, args.udp_listen_port)
    )

    async def one_tcp_attempt(worker_num: int) -> None:
        reader, writer = await asyncio.open_connection(args.tcp_connect_host, args.tcp_connect_port)

        await write_large_chunk_to_stream_writer(writer, tcp_client_hello(client_id))

        logger.info('TCP worker #%d started.', worker_num)

        async def recv_while_can() -> None:
            while 1:
                msg = await read_large_chunk_from_stream_reader(reader, datagram)
                alive.mark_as_alive()
                await protocol.send_datagram(msg)

        async def send_while_can() -> None:
            while 1:
                msg = await udp_to_tcp_queue.get()
                alive.mark_as_alive()
                await write_large_chunk_to_stream_writer(writer, msg)

        await asyncio.gather(
            recv_while_can(),
            send_while_can(),
        )

    async def one_worker(worker_num: int) -> None:
        while 1:
            try:
                await one_tcp_attempt(worker_num)
            except Exception as exc:
                # print(traceback.format_exc())
                logger.warning('TCP worker #%d stopped with an error: %r.', worker_num, exc)
            await asyncio.sleep(args.reconnect_interval)

    async def run_workers() -> None:
        await asyncio.gather(
            *[
                one_worker(i)
                for i in range(args.workers)
            ]
        )

    try:
        await run_workers()
    finally:
        transport.close()

############################################################################################################################

def main(argv: list[str]) -> None:
    parser = argparse.ArgumentParser()

    parser.add_argument('--log-level', default='INFO', required=False, choices=logging_levels_case_insensitive, type=always_upper_str)

    subparsers : subparsers_as_dataclass[Callable[[Any], Coroutine[Any, Any, None]]]
    subparsers = subparsers_as_dataclass(
        parser.add_subparsers(dest='mode', required=True)
    )

    subparsers.add_subparser_from_dataclass('server', server_args, server_main)

    subparsers.add_subparser_from_dataclass('client', client_args, client_main)

    args = parser.parse_args(argv)

    logging.basicConfig(
        level=cast(str, args.log_level).upper(),
        style='{',
        format='{asctime} {levelname:^8s} {funcName}:{lineno} {message}',
        # stream=...,
    )

    logger.debug(args)

    parser_name = args.mode
    assert isinstance(parser_name, str)
    handler, arg = subparsers.get_handler(args)

    try:
        asyncio.run(handler(arg))
    except KeyboardInterrupt:
        pass

if __name__ == '__main__':
    main(sys.argv[1:])
