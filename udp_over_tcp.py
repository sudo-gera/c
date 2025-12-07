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
from typing import *
from functools import *
from itertools import *
from operator import *
from dataclasses import *
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from _typeshed import DataclassInstance

if sys.version_info < (3, 11):
    from collections.abc import Callable as caCallable
    call_R = TypeVar("call_R")
    call_P = ParamSpec("call_P")
    def call(obj: caCallable[call_P, call_R], /, *args: call_P.args, **kwargs: call_P.kwargs) -> call_R:
        return obj(*args, **kwargs)

############################################################################################################################

subparsers_as_dataclass_handler_type = TypeVar('subparsers_as_dataclass_handler_type')

@dataclass
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

        if isinstance(field_type, types.UnionType):
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

@dataclass
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

@dataclass
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

        def write(self, data: bytes) -> None:
            if self._closed:
                raise RuntimeError("Transport is closed")

            self._write_buffer_size += len(data)
            loop = asyncio.get_running_loop()
            # Schedule delivery to mimic real async transports
            loop.call_soon(self._deliver, data)

        def _deliver(self, data: bytes) -> None:
            try:
                self._protocol.data_received(data)
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



@dataclass
class datagram:
    src_host: str
    src_port: int
    dst_host: str
    dst_port: int
    data: bytes
    client_id: bytes

    # @classmethod
    # def from_async_streamreader(cls, reader: asyncio.StreamReader):
    #     ...
    
    # def to_async_streamwriter(cls, writer: asyncio.StreamWriter):
        

############################################################################################################################


@dataclass
class server_args:
    tcp_listen_host: str
    tcp_listen_port: int

    timeout: float

    datagram_buffer_len: int

async def server_main(args: server_args) -> None:
    print(args)

############################################################################################################################

@dataclass
class client_args:
    tcp_connect_host: str
    tcp_connect_port: int

    udp_listen_host: str
    udp_listen_port: int

    udp_connect_host: str
    udp_connect_port: int

    datagram_buffer_len: int

async def client_main(args: client_args) -> None:

    client_id = random.randbytes(16)

    udp_to_tcp_queue: asyncio.Queue[datagram] = asyncio.Queue(maxsize=args.datagram_buffer_len)

    class udp_server_protocol(asyncio.DatagramProtocol):

        def connection_made(self, transport: asyncio.BaseTransport) -> None:
            self.transport = cast(asyncio.DatagramTransport, transport)

        def datagram_received(self, data: bytes, weird_src_addr: tuple[str | Any, int]) -> None:
            src_host, src_port = weird_src_addr
            assert isinstance(src_host, str)
            src_addr = src_host, src_port

            msg = datagram(
                src_host=src_host,
                src_port=src_port,
                dst_host=args.udp_connect_host,
                dst_port=args.udp_connect_port,
                data=data,
                client_id=client_id,
            )

            if not udp_to_tcp_queue.full():
                udp_to_tcp_queue.put_nowait(msg)
        
        def send_datagramm(self, msg: datagram) -> None:
            self.transport.sendto(
                data = msg.data,
                addr = (
                    msg.dst_host,
                    msg.dst_port,
                ),
            )

    loop = asyncio.get_running_loop()

    transport, protocol = await loop.create_datagram_endpoint(
        udp_server_protocol,
        local_addr=(args.udp_listen_host, args.udp_listen_port)
    )

    # class one_tcp_attempt:
        
    #     async def main():
    #         reader, writer = await asyncio.open_connection(args.tcp_connect_host, args.tcp_connect_port)


    try:
        await asyncio.Future()
    finally:
        transport.close()

############################################################################################################################

if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    subparsers : subparsers_as_dataclass[Callable[[Any], Coroutine[Any, Any, None]]]
    subparsers = subparsers_as_dataclass(
        parser.add_subparsers(dest='mode', required=True)
    )

    subparsers.add_subparser_from_dataclass('server', server_args, server_main)

    subparsers.add_subparser_from_dataclass('client', client_args, client_main)

    args = parser.parse_args()

    parser_name = args.mode
    assert isinstance(parser_name, str)
    handler, arg = subparsers.get_handler(args)
    
    asyncio.run(handler(arg))


