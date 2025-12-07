from __future__ import annotations
import asyncio
import argparse
from typing import *
import types
from functools import *
from itertools import *
from operator import *
from dataclasses import dataclass, fields, asdict
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from _typeshed import DataclassInstance

@dataclass
class server_args:
    tcp_listen_host: str
    tcp_listen_port: int

    timeout: float

@dataclass
class client_args:
    tcp_listen_host: str
    tcp_listen_port: int

    udp_listen_host: str
    udp_listen_port: int

    udp_connect_host: str
    udp_connect_port: int

    connection_name: str | None

subparsers_as_dataclass_handler_type = TypeVar('subparsers_as_dataclass_handler_type')

@dataclass
class subparsers_as_dataclass_parser_ctx(Generic[subparsers_as_dataclass_handler_type]):
    dataclass: type[DataclassInstance]
    handler: subparsers_as_dataclass_handler_type

class subparsers_as_dataclass(Generic[subparsers_as_dataclass_handler_type]):

    def __init__(self, subparsers : argparse._SubParsersAction[argparse.ArgumentParser]):
        self.subparsers = subparsers
        self.dataclasses : dict[str, subparsers_as_dataclass_parser_ctx[subparsers_as_dataclass_handler_type]] = {}

    def add_subparser_from_dataclass(self, parser_name: str, args_dataclass: type[DataclassInstance], handler: subparsers_as_dataclass_handler_type) -> None:
        parser = self.subparsers.add_parser(parser_name)
        for field in fields(args_dataclass):
            arg_name = field.name
            arg_required : bool|None = None
            arg_type : type[Any]|None = None
            assert isinstance(field.type, str)
            field_type = eval(field.type)
            if isinstance(field_type, type):
                arg_type = field_type
                arg_required = True
            if isinstance(field_type, types.UnionType):
                union_args = field_type.__args__
                if len(union_args) == 2:
                    if type(None) in union_args:
                        not_none = union_args[union_args[0] == None]
                        if isinstance(not_none, type):
                            arg_type = not_none
                            arg_required = False
            assert arg_type is not None
            assert arg_required is not None
            parser.add_argument(
                '--' + arg_name.replace('_', '-'),
                required=arg_required,
                type=arg_type
            )
        assert parser_name not in self.dataclasses
        self.dataclasses[parser_name] = subparsers_as_dataclass_parser_ctx(
            args_dataclass,
            handler,
        )

    def get_handler(self, args: argparse.Namespace) -> tuple[subparsers_as_dataclass_handler_type, DataclassInstance]:
        ctx = self.dataclasses[self.subparsers.dest]
        dataclass_attrs = {field.name for field in fields(ctx.dataclass)}
        return ctx.handler, ctx.dataclass(**{k:v for k,v in vars(args).items() if k in dataclass_attrs})


async def server_main(args: server_args) -> None:
    print(args)

async def client_main(args: client_args) -> None:
    print(args)

if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    subparsers : subparsers_as_dataclass[Callable[[Any], Coroutine[Any, Any, None]]] = subparsers_as_dataclass(parser.add_subparsers(dest='parser_name', required=True))

    subparsers.add_subparser_from_dataclass('server', server_args, server_main)

    subparsers.add_subparser_from_dataclass('client', client_args, client_main)

    args = parser.parse_args()

    parser_name = args.parser_name
    assert isinstance(parser_name, str)
    handler, arg = subparsers.get_handler(args)
    
    asyncio.run(handler(arg))


