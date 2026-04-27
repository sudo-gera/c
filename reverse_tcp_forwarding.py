from __future__ import annotations
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
############################################################################################################################

alive = alive_or_raise(60)

############################################################################################################################

@dataclass(frozen=True)
class main_args:
    mode: Literal['client', 'server']
    tcp_host: str
    tcp_port: int
    cmd_host: str
    cmd_port: int
    log_level: LogLevelEnum

async def copy(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    while (data := await reader.read(2**16)):
        logging.debug(f'{data!r}')
        writer.write(data)
        await writer.drain()
    writer.write_eof()

async def copy_both(tcp_connection: tuple[asyncio.StreamReader, asyncio.StreamWriter], cmd_connection: tuple[asyncio.StreamReader, asyncio.StreamWriter], f: asyncio.Future[None]) -> None:
    try:
        await gather(
            copy(tcp_connection[0], cmd_connection[1]),
            copy(cmd_connection[0], tcp_connection[1]),
        )
    except Exception as e:
        logging.warning('\n'+traceback.format_exc())
        pass
    finally:
        logging.debug(f'setting {id(f) = }')
        f.set_result(None)

async def one_client_attempt(args: main_args) -> None:
    try:
        logging.debug('starting client attempt')
        tcp_reader, tcp_writer = await asyncio.open_connection(args.tcp_host, args.tcp_port)
        try:
            cmd_reader, cmd_writer = await asyncio.open_connection(args.cmd_host, args.cmd_port)
            try:
                await gather(
                    copy(tcp_reader, cmd_writer),
                    copy(cmd_reader, tcp_writer),
                )
            finally:
                cmd_writer.close()
                await cmd_writer.wait_closed()
        finally:
            tcp_writer.close()
            await tcp_writer.wait_closed()
    except Exception as e:
        logging.warning('\n'+traceback.format_exc())
        pass

tcp_connection_ids : dict[uuid.UUID, tuple[asyncio.StreamReader, asyncio.StreamWriter] | asyncio.Future[None]] = {}
cmd_connection_ids : dict[uuid.UUID, tuple[asyncio.StreamReader, asyncio.StreamWriter] | asyncio.Future[None]] = {}

async def connection_matcher(args: main_args) -> None:
    while True:
        await asyncio.sleep(0.1)
        for tcp_id in tcp_connection_ids:
            for cmd_id in cmd_connection_ids:
                tcp_connection = tcp_connection_ids[tcp_id]
                cmd_connection = cmd_connection_ids[cmd_id]
                if isinstance(tcp_connection, tuple):
                    if isinstance(cmd_connection, tuple):
                        logging.debug(f'matching {tcp_id = } and {cmd_id}')
                        f : asyncio.Future[None] = asyncio.Future()
                        tcp_connection_ids[tcp_id] = f
                        cmd_connection_ids[cmd_id] = f
                        fire(copy_both(tcp_connection, cmd_connection, f))

async def on_incoming_tcp(args: main_args, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        my_id = uuid.uuid4()
        tcp_connection_ids[my_id] = (reader, writer)
        logging.debug(f'accepted {my_id = } starting to wait')
        await asyncio.sleep(4)
        f = tcp_connection_ids.pop(my_id)
        if isinstance(f, asyncio.Future):
            logging.debug(f'accepted {my_id = } starting to wait on {id(f) = }')
            await f
            logging.debug(f'accepted {my_id = } done waiting on {id(f) = }')
        else:
            logging.debug(f'accepted {my_id = } no future')
    finally:
        writer.close()
        await writer.wait_closed()

async def on_incoming_cmd(args: main_args, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        my_id = uuid.uuid4()
        cmd_connection_ids[my_id] = (reader, writer)
        logging.debug(f'accepted {my_id = } starting to wait')
        await asyncio.sleep(4)
        f = cmd_connection_ids.pop(my_id)
        if isinstance(f, asyncio.Future):
            logging.debug(f'accepted {my_id = } starting to wait on {id(f) = }')
            await f
            logging.debug(f'accepted {my_id = } done waiting on {id(f) = }')
        else:
            logging.debug(f'accepted {my_id = } no future')
    finally:
        writer.close()
        await writer.wait_closed()

async def main(args: main_args) -> None:

    set_log_level(args.log_level)

    if args.mode == 'client':
        while True:
            await asyncio.sleep(1)
            fire(one_client_attempt(args))

    if args.mode == 'server':
        fire(connection_matcher(args))

        async with await asyncio.start_server(partial(on_incoming_tcp, args), args.tcp_host, args.tcp_port) as tcp_server:
            async with await asyncio.start_server(partial(on_incoming_cmd, args), args.cmd_host, args.cmd_port) as cmd_server:
                await gather(
                    tcp_server.serve_forever(),
                    cmd_server.serve_forever(),
                )

    assert False

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    setup_parser_from_dataclass(parser, main_args)
    asyncio.run(main(dict_to_dataclass(vars(parser.parse_args()), main_args)))
