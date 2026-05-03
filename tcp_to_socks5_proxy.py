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

class LogLevelEnum(Enum):
    CRITICAL = 50
    FATAL = CRITICAL
    ERROR = 40
    WARNING = 30
    WARN = WARNING
    INFO = 20
    DEBUG = 10
    NOTSET = 0

def set_log_level(log_level: LogLevelEnum | int) -> None:
    if isinstance(log_level, LogLevelEnum):
        log_level = log_level.value
    assert isinstance(log_level, int)
    logging.basicConfig(
        level=log_level,
        style='{',
        format='{asctime:s} {levelname:^8s} {funcName}:{lineno} {message}',
    )

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
        return value in args

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

@typed_cache
def get_fields(dclass: type[DataclassInstance]) -> list[dataclass_field]:

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
        arg_type : Callable[[str], Any]|None = None
        arg_default : Any = None
        arg_choices : Any = None

        if field.field.default is not MISSING: # v: t = SOME_DEFAULT
            arg_default = field.field.default
            arg_required = False

        if field.field.default_factory is not MISSING: # v: t = field(default_factory=SOME_CALLABLE)
            arg_default = field.field.default_factory()
            arg_required = False

        target_type = field.type

        if (
            sys.version_info >= (3, 10)
            and
            typing.get_origin(target_type) is types.UnionType  # t | None
            or
            typing.get_origin(target_type) is typing.Union  # typing.Optional[t], typing.Union[t, None], typing.Union[t, type(None)]
        ):
            union_args = typing.get_args(target_type)
            assert len(union_args) == 2
            assert type(None) in union_args
            target_type = union_args[union_args[0] == type(None)]
            assert target_type is not None
            arg_required = False

        if isinstance(target_type, type):
            if issubclass(target_type, Enum | EnumMeta):
                enum_members = target_type.__members__
                assert isinstance(enum_members, types.MappingProxyType)
                enum_members_dict = {name: enum_members.get(name) for name in enum_members.keys()}
                def get_enum(user_input: str) -> Enum | EnumMeta:
                    if user_input not in enum_members_dict:
                        raise ValueError
                    enum = enum_members_dict[user_input]
                    if not isinstance(enum, Enum | EnumMeta):
                        raise ValueError
                    return enum
                arg_type=get_enum
                arg_choices=list(map(get_enum, enum_members_dict))
            else:
                arg_type = target_type

        elif typing.get_origin(target_type) is typing.Literal:
            literal_args = typing.get_args(target_type)
            literal_types = {type(arg) for arg in literal_args}
            assert len(literal_types)
            literal_type = literal_types.pop()
            arg_choices = literal_args
            arg_type = literal_type

        assert arg_type is not None

        parser.add_argument(
            '--' + arg_name.replace('_', '-'),
            required=arg_required,
            type=arg_type,
            default=arg_default,
            choices=arg_choices,
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

@typed_cache
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

def can_use_event_loop() -> bool:
    try:
        loop = asyncio.get_running_loop()
        return True
    except RuntimeError:
        return False

############################################################################################################################

class alive_or_raise:

    def __init__(self, timeout: float) -> None:
        self.__timeout = timeout
        self.__started = False
        self.mark_as_alive()

    def mark_as_alive(self) -> None:

        if not self.__started and can_use_event_loop():
            fire(self.__checker())
            self.__started = True

        self.__raise_at = time.time() + self.__timeout

    async def __checker(self) -> None:
        while 1:
            current_time = time.time()
            until_raise = self.__raise_at - current_time
            if until_raise <= 0:
                raise KeyboardInterrupt
            await asyncio.sleep(until_raise)

############################################################################################################################

if_main_parse_args_and_asyncio_run_arg = TypeVar('if_main_parse_args_and_asyncio_run_arg', bound=DataclassInstance)

def if_main_parse_args_and_asyncio_run(main: Callable[[if_main_parse_args_and_asyncio_run_arg], Any]) -> Any:
    if __name__ != '__main__':
        return
    hints = typing.get_type_hints(main)
    hints.pop('return', None)
    assert len(hints) == 1
    main_args = [*hints.values()][0]
    assert not TYPE_CHECKING or isinstance(main_args, type)
    parser = argparse.ArgumentParser()
    setup_parser_from_dataclass(parser, main_args)
    args = parser.parse_args()
    asyncio.run(main(main_args(**vars(args))))

############################################################################################################################

@dataclass(frozen=True)
class main_args:

    listen_host: str
    listen_port: int

    proxy_host: str
    proxy_port: int

    forward_host: str
    forward_port: int

    log_level: LogLevelEnum = LogLevelEnum.INFO

class addr_types(Enum):
    IPv4           = b'\x01'
    domain_name    = b'\x03'
    IPv6           = b'\x04'

async def copy(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    while (data := await reader.read(2**16)):
        logging.debug(f"{data!r}")
        writer.write(data)
        await writer.drain()
    writer.write_eof()

async def on_client(args: main_args, accepted_reader: asyncio.StreamReader, accepted_writer: asyncio.StreamWriter) -> None:
    try:
        logging.info(f"accepted")

        connected_reader, connected_writer = await asyncio.open_connection(args.proxy_host, args.proxy_port)
        try:
            logging.info(f"connected")

            addr_type : addr_types | None = None

            try:
                ip = ipaddress.ip_address(args.forward_host)
                addr = ip.packed
                if ip.version == 4:
                    addr_type = addr_types.IPv4
                elif ip.version == 6:
                    addr_type = addr_types.IPv4
                else:
                    assert False
            except ValueError:
                addr_type = addr_types.domain_name
                addr = args.forward_host.encode()
                addr = len(addr).to_bytes(1, 'big') + addr
            
            port = args.forward_port.to_bytes(2, 'big')

            assert addr_type is not None

            #                         . socks version
            #                         |   . auth methods array len
            #                         |   |   . no auth
            #                         |   |   |   . socks version
            #                         |   |   |   |   . CONNECT command
            #                         |   |   |   |   |   . reserved, must be \x00
            #                         |   |   |   |   |   |      . addr type
            #                         |   |   |   |   |   |      |                 . addr value
            #                         |   |   |   |   |   |      |                 |      . port
            #                         |   |   |   |   |   |      |                 |      |
            connected_writer.write(b'\x05\x01\x00\x05\x01\x00' + addr_type.value + addr + port)
            await connected_writer.drain()

            logging.info(f"sent socks5 request")

            #                                  . socks version
            #                                  |   . selected auth method
            #                                  |   |   . socks version
            #                                  |   |   |   . status code
            #                                  |   |   |   |   . reserved, must be \x00
            #                                  |   |   |   |   |
            await connected_reader.readexactly(1 + 1 + 1 + 1 + 1)
            addr_type = addr_types(await connected_reader.readexactly(1))
            if addr_type is addr_types.IPv4:
                await connected_reader.readexactly(4)
            elif addr_type is addr_types.domain_name:
                l, = await connected_reader.readexactly(1)
                await connected_reader.readexactly(l)
            elif addr_type is addr_types.IPv6:
                await connected_reader.readexactly(16)
            else:
                assert False
            await connected_reader.readexactly(2)

            logging.info(f"got socks5 response")

            await gather(
                copy(accepted_reader, connected_writer),
                copy(connected_reader, accepted_writer),
            )

        finally:
            connected_writer.close()
            await connected_writer.wait_closed()
            logging.info(f"closing connected")
    finally:
        accepted_writer.close()
        await accepted_writer.wait_closed()
        logging.info(f"closing accepted")

@if_main_parse_args_and_asyncio_run
async def main(args: main_args) -> None:
    
    set_log_level(args.log_level)

    async with await asyncio.start_server(partial(on_client, args), args.listen_host, args.listen_port) as server:
        await server.serve_forever()
