from __future__ import annotations
import asyncio
import argparse
import types
import json
import base64
import random
import math
import fractions
import sys
import traceback
import contextlib
import logging
import os
import uuid
import socket
import ipaddress
from typing import *
from functools import *
from itertools import *
from operator import *
from dataclasses import *
from collections import *

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

logger = logging.getLogger(__name__)

class always_upper_str(str):
    def __new__(cls, *args: Any, **kwargs: Any) -> always_upper_str:
        value = str(*args, **kwargs).upper()
        return super().__new__(cls, value)

logging_levels = [name for name in dir(logging) if isinstance(logging.getLevelName(name), int)]

logging_levels_case_insensitive = [always_upper_str(a) for a in logging_levels]

############################################################################################################################

subparsers_as_dataclass_handler_type = TypeVar('subparsers_as_dataclass_handler_type')

@dataclass(frozen=True)
class subparsers_as_dataclass_parser_ctx(Generic[subparsers_as_dataclass_handler_type]):
    dataclass: type[DataclassInstance]
    handler: subparsers_as_dataclass_handler_type

def setup_parser_from_dataclass(parser: argparse.ArgumentParser, args_dataclass: type[DataclassInstance]) -> None:
    for field in fields(args_dataclass):

        arg_name = field.name
        arg_required = True
        arg_type : type[Any]|None = None
        arg_default : Any = None

        assert isinstance(field.type, str)
        field_type = eval(field.type)

        if field.default is not MISSING:
            arg_default = field.default
            arg_required = False
        
        if field.default_factory is not MISSING:
            arg_default = field.default_factory()
            arg_required = False

        if isinstance(field_type, type):
            arg_type = field_type

        if sys.version_info >= (3, 9):
            if isinstance(field_type, types.UnionType):
                union_args = field_type.__args__
                assert len(union_args) == 2
                assert not arg_required
                assert type(arg_default) in union_args
                non_default_type = union_args[union_args[0] == type(arg_default)]
                assert isinstance(non_default_type, type)
                arg_type = non_default_type

        if get_origin(field_type) is Union:
            union_args = field_type.__args__
            assert len(union_args) == 2
            assert not arg_required
            assert type(arg_default) in union_args
            non_default_type = union_args[union_args[0] == type(arg_default)]
            assert isinstance(non_default_type, type)
            arg_type = non_default_type

        assert arg_type is not None
        assert arg_required is not None

        parser.add_argument(
            '--' + arg_name.replace('_', '-'),
            required=arg_required,
            type=arg_type,
            default=arg_default,
        )


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
        dataclass_attrs = {field.name for field in fields(ctx.dataclass)}
        return ctx.handler, ctx.dataclass(**{k:v for k,v in vars(args).items() if k in dataclass_attrs})

############################################################################################################################

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

    for field in fields(cls):
        assert isinstance(field.type, str)
        field_type = eval(field.type)
        assert isinstance(field_type, type)

    @reads_from_stream_reader(cls)
    async def read_something_from_stream_reader(reader: asyncio.StreamReader) -> Any:

        async def read_one_field(field: Field[Any]) -> Any:
            assert isinstance(field.type, str)
            field_type = eval(field.type)
            assert isinstance(field_type, type)
            value: Any = await read_from_stream_reader(reader, field_type)
            return value
        
        return cls(
            **{
                field.name: await read_one_field(field)
                for field in fields(cls)
            }
        )

    @writes_to_stream_writer(cls)
    async def write_something_to_stream_writer(writer: asyncio.StreamWriter, value: Any) -> None:
        for field in fields(cls):
            assert isinstance(field.type, str)
            field_type = eval(field.type)
            assert isinstance(field_type, type)
            field_value = getattr(value, field.name)
            assert type(field_value) == field_type
            await write_to_stream_writer(writer, field_value)
    
@call
def setup_default_types() -> None:
    # bytes

    @reads_from_stream_reader(bytes)
    async def read_bytes_from_stream_reader(reader: asyncio.StreamReader) -> bytes:
        data_len = int.from_bytes(await reader.readexactly(8), 'little')
        data = await reader.readexactly(data_len)
        return data

    @writes_to_stream_writer(bytes)
    async def write_bytes_to_stream_writer(writer: asyncio.StreamWriter, value: bytes) -> None:
        writer.write(len(value).to_bytes(8, 'little'))
        writer.write(value)
        await writer.drain()

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

@call
def reader_and_writer_test() -> None:
    import asyncio
    from asyncio import BaseTransport, Transport, StreamReader, StreamWriter
    from asyncio import AbstractEventLoop


    class MemoryTransport(Transport):
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
    ) -> tuple[StreamReader, StreamWriter]:
        """
        Create a pure in-memory pair compatible with StreamReader/StreamWriter.
        Fully mypy-checked.
        """

        loop: AbstractEventLoop = asyncio.get_running_loop()
        reader: StreamReader = StreamReader()
        protocol: asyncio.StreamReaderProtocol = asyncio.StreamReaderProtocol(reader)

        transport: MemoryTransport = MemoryTransport(protocol, extra=extra_info)
        protocol.connection_made(transport)

        writer: StreamWriter = StreamWriter(transport, protocol, reader, loop)
        return reader, writer

    async def main() -> None:
        reader, writer = await create_in_memory_stream()

        for value in [b'123\x00123\n123', bytearray(b'123\x00123\n123'), 'œ', 0, 1, -1, 0.1+0.2]:
            await write_to_stream_writer(writer, value)
            assert value == await read_from_stream_reader(reader, type(value))

        writer.close()
        assert not await reader.read()

    asyncio.run(main())

############################################################################################################################

put_rotate_type = TypeVar('put_rotate_type')

def put_rotate(q: asyncio.Queue[put_rotate_type], v: put_rotate_type) -> None:
    if q.full():
        q.get_nowait()
    q.put_nowait(v)

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

tasks : set[asyncio.Task[None]] = set()

def fire(coro: Awaitable[Any]) -> None:
    async def wrapper() -> None:
        await coro
    task : asyncio.Task[None] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

############################################################################################################################

@dataclass(frozen=True)
class connection_info:
    src_host: str
    src_port: int
    dst_host: str
    dst_port: int
    connection_id: uuid.UUID
    client_id: uuid.UUID

    def reverse(self) -> connection_info:
        return replace(
            self,
            src_host=self.dst_host,
            src_port=self.dst_port,
            dst_host=self.src_host,
            dst_port=self.src_port,
        )

setup_reader_and_writer_for_dataclass(connection_info)

@dataclass(frozen=True)
class datagram:
    connection: connection_info
    data: bytes

setup_reader_and_writer_for_dataclass(datagram)

@dataclass(frozen=True)
class tcp_client_hello:
    client_id: uuid.UUID

setup_reader_and_writer_for_dataclass(tcp_client_hello)

############################################################################################################################

@dataclass(frozen=True)
class server_args:
    tcp_listen_host: str
    tcp_listen_port: int

    timeout: float

    datagram_buffer_len: int

async def server_main(args: server_args) -> None:
    
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
        connection_client_to_server: connection_info
        transport_future: asyncio.Future[asyncio.DatagramTransport] = field(default_factory=asyncio.Future)

        def __post_init__(self) -> None:
            self.connection_server_to_client = self.connection_client_to_server.reverse()

        def connection_made(self, transport: asyncio.BaseTransport) -> None:

            connection_id = self.connection_server_to_client.connection_id

            logger.info(f'UDP client for {connection_id = } connected.')

            self.transport_future.set_result(
                cast(
                    asyncio.DatagramTransport,
                    transport
                )
            )

        def datagram_received(self, data: bytes, weird_src_addr: tuple[str | Any, int]) -> None:
            print(f'{weird_src_addr = !r}')
            src_host, src_port = weird_src_addr
            assert isinstance(src_host, str)
            addr = src_host, src_port

            connection = self.connection_server_to_client

            msg = datagram(
                connection=connection,
                data=data,
            )

            logger.debug(f'External datagram: {len(msg.data)} bytes from {msg.connection}.')

            client_context = get_tcp_client_context(client_id=connection.client_id)

            put_rotate(client_context.server_to_client_queue, msg)

        async def send_datagram(self, msg: datagram) -> None:

            logger.debug(f'Internal datagram: {len(msg.data)} bytes from {msg.connection}.')

            transport = await self.transport_future

            transport.sendto(
                data = msg.data,
            )

        def error_received(self, exc: Exception) -> None:
            logger.warning(f'UDP server received an error: {exc!r}')

        def connection_lost(self, exc: Exception | None) -> None:
            logger.warning(f'UDP server stopped with an error: {exc!r}')

    udp_clients : dict[uuid.UUID, udp_client_protocol] = {}

    async def get_udp_client(msg: datagram) -> udp_client_protocol:
        if msg.connection.connection_id not in udp_clients:

            dst_hosts = [msg.connection.dst_host]

            if not is_ip(dst_hosts[0]):
                logger.debug(f'Resolving domain {dst_hosts[0]!r}...')
                dst_hosts = await resolve_domain(dst_hosts[0])
                logger.debug(f'Resolved into {dst_hosts}')

            dst_host = random.choice(dst_hosts)

            if len(dst_hosts) > 1:
                logger.debug(f'DNS returned mulitple IPs, randomly selecting {dst_host!r}.')

            msg = replace(
                msg,
                connection=replace(
                    msg.connection,
                    dst_host=dst_host,
                )
            )

            loop = asyncio.get_running_loop()
            transport, protocol = await loop.create_datagram_endpoint(
                lambda: udp_client_protocol(msg.connection),
                remote_addr=(msg.connection.dst_host, msg.connection.dst_port),
            )

            udp_clients[msg.connection.connection_id] = protocol
        return udp_clients[msg.connection.connection_id]

    async def on_tcp_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
        with contextlib.closing(writer):
            try:

                client_hello = await read_from_stream_reader(reader, tcp_client_hello)

                context = get_tcp_client_context(client_hello.client_id)

                client_id = context.client_id
                logger.info(f'TCP client {client_id = } connected.')

                async def recv_while_can() -> None:
                    while 1:
                        msg = await read_from_stream_reader(reader, datagram)

                        udp_client = await get_udp_client(msg)
                        await udp_client.send_datagram(msg)
                
                async def send_while_can() -> None:
                    while 1:
                        msg = await context.server_to_client_queue.get()
                        await write_to_stream_writer(writer, msg)
                
                await asyncio.gather(
                    recv_while_can(),
                    send_while_can(),
                )
            
            except Exception as exc:
                try:
                    client_id_str = str(context.client_id)
                except Exception:
                    client_id_str = '(unknown)'
                print(traceback.format_exc())
                logger.warning(f'TCP client #{client_id_str} stopped with an error: {exc!r}')

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

    resolve_dns_on_client: bool = False

async def client_main(args: client_args) -> None:

    addr_to_id : dict[tuple[str, int], uuid.UUID] = {}

    udp_to_tcp_queue: asyncio.Queue[datagram] = asyncio.Queue(maxsize=args.datagram_buffer_len)

    client_id = uuid.uuid4()

    dst_hosts = [args.udp_connect_host]
    if not is_ip(dst_hosts[0]):
        if args.resolve_dns_on_client:
            logger.debug(f'Resolving {dst_hosts[0]!r}...')
            dst_hosts = await resolve_domain(dst_hosts[0])
            logger.debug(f'Resolved into {dst_hosts}')
        else:
            logger.debug(f'Domain {dst_hosts[0]!r} will be resolved on server.')
    assert dst_hosts

    dst_port = args.udp_connect_port

    @dataclass(frozen=True)
    class udp_server_protocol(asyncio.DatagramProtocol):
        transport_future: asyncio.Future[asyncio.DatagramTransport] = field(default_factory=asyncio.Future)

        def connection_made(self, transport: asyncio.BaseTransport) -> None:

            logger.info(f'UDP server started, assigning {client_id = }')

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
                logger.info(f'new UDP connection from [{src_host}]:{src_port}, assigning {connection_id = }')
            
            connection_id = addr_to_id[addr]

            dst_host = random.choice(dst_hosts)

            if len(dst_hosts) > 1:
                logger.debug(f'DNS returned mulitple IPs, randomly selecting {dst_host!r}.')

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

            logger.debug(f'External datagram: {len(msg.data)} bytes from {msg.connection}.')

            put_rotate(udp_to_tcp_queue, msg)

        async def send_datagram(self, msg: datagram) -> None:

            logger.debug(f'Internal datagram: {len(msg.data)} bytes from {msg.connection}.')

            transport = await self.transport_future

            transport.sendto(
                data = msg.data,
                addr = (
                    msg.connection.dst_host,
                    msg.connection.dst_port,
                ),
            )

        def error_received(self, exc: Exception) -> None:
            logger.warning(f'UDP server received an error: {exc!r}')

        def connection_lost(self, exc: Exception | None) -> None:
            logger.warning(f'UDP server stopped with an error: {exc!r}')

    loop = asyncio.get_running_loop()

    transport, protocol = await loop.create_datagram_endpoint(
        udp_server_protocol,
        local_addr=(args.udp_listen_host, args.udp_listen_port)
    )

    async def one_tcp_attempt(worker_num: int) -> None:
        reader, writer = await asyncio.open_connection(args.tcp_connect_host, args.tcp_connect_port)

        await write_to_stream_writer(writer, tcp_client_hello(client_id))

        logger.info(f'TCP worker #{worker_num} started.')

        async def recv_while_can() -> None:
            while 1:
                msg = await read_from_stream_reader(reader, datagram)
                await protocol.send_datagram(msg)
        
        async def send_while_can() -> None:
            while 1:
                msg = await udp_to_tcp_queue.get()
                await write_to_stream_writer(writer, msg)
        
        await asyncio.gather(
            recv_while_can(),
            send_while_can(),
        )

    async def one_worker(worker_num: int) -> None:
        while 1:
            try:
                await one_tcp_attempt(worker_num)
            except Exception as exc:
                logger.warning(f'TCP worker #{worker_num} stopped with an error: {exc!r}')
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

if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument('--log-level', default='INFO', required=False, choices=logging_levels_case_insensitive, type=always_upper_str)

    subparsers : subparsers_as_dataclass[Callable[[Any], Coroutine[Any, Any, None]]]
    subparsers = subparsers_as_dataclass(
        parser.add_subparsers(dest='mode', required=True)
    )

    subparsers.add_subparser_from_dataclass('server', server_args, server_main)

    subparsers.add_subparser_from_dataclass('client', client_args, client_main)

    args = parser.parse_args()

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


