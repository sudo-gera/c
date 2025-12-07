from __future__ import annotations
import asyncio
import argparse
from typing import *
import types
from functools import *
from itertools import *
from operator import *
from dataclasses import dataclass, fields
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from _typeshed import DataclassInstance

@dataclass
class server_args:
    tcp_listen_host: str
    tcp_listen_port: int

@dataclass
class client_args:
    tcp_listen_host: str
    tcp_listen_port: int

    udp_listen_host: str
    udp_listen_port: int

    udp_connect_host: str
    udp_connect_port: int

    connection_name: str | None

async def server_main():
    ...

async def client_main():
    ...

def add_subparser_from_dataclass(subparsers: argparse._SubParsersAction, parser_name: str, args_dataclass: type[DataclassInstance]):
    parser = subparsers.add_parser(parser_name)
    for field in fields(args_dataclass):
        optional : bool|None = None
        arg_type : type[Any]|None = None
        if isinstance(field.type, type):
            arg_type = field.type
            optional = False
        if isinstance(fields.type, types.UnionType):
            union_args = field.type.__args__
            if len(union_args) == 2:
                if None in union_args:
                    not_none = union_args[union_args[0] == None]
                    if isinstance(not_none, type):
                        arg_type = not_none
                        optional = True
        assert arg_type is not None
        assert optional is not None
        parser.add


if __name__ == '__main__':


    parser = argparse.ArgumentParser()

    subparsers = parser.add_subparsers(dest='mode', required=True)

    for field in fields(subparsers.add_parser('server')):
        types : list[type] = []
        if isinstance(field.type, types.UnionType):
            field.ty


        subparsers.add_parser(
            name='--' + field.name.replace('-','_'),
            required=
        )

    client_parser = subparsers.add_parser('client')


    args = parser.parse_args()


