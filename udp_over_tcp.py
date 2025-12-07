from __future__ import annotations
import asyncio
import argparse
import types
import json
import base64
import random
from typing import *
from functools import *
from itertools import *
from operator import *
from dataclasses import *
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from _typeshed import DataclassInstance

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

# def dataclass_to_json_bytes(obj: DataclassInstance) -> bytes:
#     return json.dumps(vars(obj)).encode()

# json_to_dataclass_type = TypeVar('json_to_dataclass_type')

# def json_to_dataclass(data: bytes, dataclass_type: type[json_to_dataclass_type]) -> json_to_dataclass_type:
#     return dataclass_type(**json.loads(data.decode()))

############################################################################################################################

read_from_stream_reader_type = TypeVar('read_from_stream_reader_type')

async def read_from_stream_reader(reader: asyncio.StreamReader, type_to_read: type[read_from_stream_reader_type]) -> read_from_stream_reader:
    ...

async def write_to_stream_writer(writer: asyncio.StreamWriter, value: Any) -> None:
    ...

@dataclass
class reads_from_stream_reader:
    type_to_read: type[Any]

    def __call__(self, Callable[[], None]):
        ...

    

############################################################################################################################



@dataclass
class datagram:
    src_host: str
    src_port: int
    dst_host: str
    dst_port: int
    data: bytes
    client_id: bytes

    @classmethod
    def from_async_streamreader(cls, reader: asyncio.StreamReader):
        ...
    
    def to_async_streamwriter(cls, writer: asyncio.StreamWriter):
        

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

    client_id = random.randbytes(16).hex()

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
                dst_host=self.args.udp_connect_host,
                dst_port=self.args.udp_connect_port,
                data_b64=base64.b64encode(data).decode(),
                client_id=client_id,
            )

            if not self.received_datagrams.full():
                self.received_datagrams.put_nowait(msg)
        
        def send_datagramm(self, msg: datagram) -> None:
            self.transport.sendto(
                data = base64.b64decode(msg.data_b64.encode()),
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

    class one_tcp_attempt:
        
        async def main():
            reader, writer = await asyncio.open_connection(args.tcp_connect_host, args.tcp_connect_port)


    try:
        await asyncio.Future()
    finally:
        transport.close()

############################################################################################################################

if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    subparsers : subparsers_as_dataclass[Callable[[Any], Coroutine[Any, Any, None]]]
    subparsers = subparsers_as_dataclass(
        parser.add_subparsers(dest='parser_name', required=True)
    )

    subparsers.add_subparser_from_dataclass('server', server_args, server_main)

    subparsers.add_subparser_from_dataclass('client', client_args, client_main)

    args = parser.parse_args()

    parser_name = args.parser_name
    assert isinstance(parser_name, str)
    handler, arg = subparsers.get_handler(args)
    
    asyncio.run(handler(arg))


