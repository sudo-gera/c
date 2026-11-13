#!/usr/bin/env python3
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
import re
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

def get_terminal_size() -> tuple[int, int] | None:
    try:
        with open('/dev/tty', 'w+') as tty:
            return os.get_terminal_size(tty.fileno())
    except OSError:
        return None

############################################################################################################################

uuid_bytes_size = len(uuid.uuid4().bytes)
uuid_hex_size = len(uuid.uuid4().hex)
uuid_str_size = len(str(uuid.uuid4()))

############################################################################################################################

false = False
true = True
null = None

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
    # If you call it from `except` block,
    # python would print stacks of both exceptions, joined by
    # 'During handling of the above exception, another exception occurred:'
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
        # Waits until first excetion or until last result
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
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], /) -> tuple[gather_t1_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], /) -> tuple[gather_t1_t, gather_t2_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], v8: Awaitable[gather_t8_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t, gather_t8_t]:
    ...

@overload
async def wait_until_all_complete_or_cancel_on_exc(v1: Awaitable[gather_t1_t], v2: Awaitable[gather_t2_t], v3: Awaitable[gather_t3_t], v4: Awaitable[gather_t4_t], v5: Awaitable[gather_t5_t], v6: Awaitable[gather_t6_t], v7: Awaitable[gather_t7_t], v8: Awaitable[gather_t8_t], v9: Awaitable[gather_t9_t], /) -> tuple[gather_t1_t, gather_t2_t, gather_t3_t, gather_t4_t, gather_t5_t, gather_t6_t, gather_t7_t, gather_t8_t, gather_t9_t]:
    ...

async def wait_until_all_complete_or_cancel_on_exc(*coro: Awaitable[Any]) -> tuple[Any, ...]:
    # Waits until first excetion or until last result
    return tuple(await _gather_impl(*coro))

gather = wait_until_all_complete_or_cancel_on_exc

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
        format='{asctime:s} {levelname:^8s} {funcName:>32s}:{lineno:<8d} {message}',
    )

############################################################################################################################

@dataclass(frozen=True)
class dataclass_field:
    field: Field[Any]
    type: Any

@typed_cache
def get_fields(dclass: type[DataclassInstance]) -> list[dataclass_field]:

    def process_one_filed(field: Field[Any]) -> dataclass_field:
        if isinstance(field.type, str):
            field_type = get_type_hints(dclass)[field.name]
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

############################################################################################################################

def setup_parser_from_dataclass(parser: argparse.ArgumentParser, args_dataclass: type[DataclassInstance]) -> None:
    for field in get_fields(args_dataclass):

        arg_name = field.field.name
        arg_required = True
        arg_type : Callable[[str], Any]|None = None
        arg_default : Any = None
        arg_choices : Any = None
        arg_action: Any = None

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

        if get_origin(target_type) is list:  # list[t]
            assert len(get_args(target_type)) == 1
            arg_type = get_args(target_type)[0]
            arg_action = 'append'
            arg_required = False
            arg_default = []

        if isinstance(target_type, type):
            if issubclass(target_type, Enum) or issubclass(target_type, EnumMeta):
                enum_members = target_type.__members__
                assert isinstance(enum_members, types.MappingProxyType)
                enum_members_dict = {name: enum_members.get(name) for name in enum_members.keys()}
                def get_enum(user_input: str) -> Enum | EnumMeta:
                    if user_input not in enum_members_dict:
                        raise ValueError
                    enum = enum_members_dict[user_input]
                    if not isinstance(enum, Enum) and not isinstance(enum, EnumMeta):
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

        if arg_type is bool:
            if arg_default:
                arg_action='store_false'
            else:
                arg_action='store_true'

        if arg_action is not None:
            parser.add_argument(
                '--' + arg_name.replace('_', '-'),
                required=arg_required,
                default=arg_default,
                action=arg_action,
            )
        else:
            parser.add_argument(
                '--' + arg_name.replace('_', '-'),
                required=arg_required,
                type=arg_type,
                default=arg_default,
                choices=arg_choices,
            )

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

@dataclass
class main_args:
    log_level: LogLevelEnum
    yggstack_executable: str
    listen: list[str]
    connect: list[str]
    remote_tcp: list[str]
    remote_udp: list[str]
    local_tcp: list[str]
    local_udp: list[str]

async def run_yggstack(args: main_args, on_line: Callable[[str], Any], stdin: str, ygg_args: list[str]) -> None:
    to_run = [args.yggstack_executable, *ygg_args]

    to_run_str = json.dumps(to_run)
    if (tsize := get_terminal_size()) is not None:
        to_run_str = min(
            to_run_str,  # used if equal
            to_run_str[:tsize[0]-4]+"...]",
            key=len,
        )
        print(to_run_str)

    process = await asyncio.create_subprocess_exec(
        *to_run,
        stdin=asyncio.subprocess.PIPE,
        stdout=asyncio.subprocess.PIPE,
    )
    try:
        assert process.stdin is not None
        assert process.stdout is not None
        process.stdin.write(stdin.encode())
        process.stdin.write_eof()
        await process.stdin.drain()
        while data := await process.stdout.readline():
            on_line(data.decode(errors='replace'))
    except BaseException:
        try:
            process.terminate()
        except ProcessLookupError as e:
            logging.warning(repr(e))
        raise
    finally:
        await process.wait()
    assert process.returncode == 0

async def yggstack_get_conf(args: main_args) -> dict[str, Any]:
    lines: list[str] = []
    await run_yggstack(args, lines.append, '', ['-genconf', '-json'])
    return cast(dict[str, Any], json.loads(''.join(lines)))

@dataclass
class ChangedPeer(Exception):
    old: ipaddress.IPv6Address | None
    new: ipaddress.IPv6Address

@dataclass
class OneProcess:
    args: main_args
    peer_ip: ipaddress.IPv6Address | None
    conf: dict[str, Any]

    def on_line(self, line: str) -> None:
        logging.debug(repr(line))
        if (match := re.search(r'\bConnected\b\s*\b(in|out)bound:\s*([a-fA-F0-9:]*)@', line)):
            peer_ip = ipaddress.ip_address(match.group(2))
            assert isinstance(peer_ip, ipaddress.IPv6Address)
            if peer_ip != self.peer_ip:
                e = ChangedPeer(old=self.peer_ip, new=peer_ip)
                logging.debug(f"{e = }")
                raise e

    def insert_peer_ip(self, forwarding: str) -> str:
        assert self.peer_ip is not None
        return re.sub(r':([^:]*)$', f":[{self.peer_ip.compressed}]:"+r'\g<1>', forwarding)

    async def main(self) -> None:
        args = ['-useconf', '-loglevel', 'debug']

        if self.peer_ip is not None:

            for arg in self.args.remote_tcp:
                args += ['--remote-tcp', arg]

            for arg in self.args.remote_udp:
                args += ['--remote-udp', arg]

            for arg in self.args.local_tcp:
                args += ['--local-tcp', self.insert_peer_ip(arg)]

            for arg in self.args.local_udp:
                args += ['--local-udp', self.insert_peer_ip(arg)]

        await run_yggstack(
            self.args,
            self.on_line,
            json.dumps(self.conf),
            args,
        )


@if_main_parse_args_and_asyncio_run
async def main(args: main_args) -> None:
    set_log_level(args.log_level)
    logging.debug(args)

    conf = await yggstack_get_conf(args)
    conf |= {
        "Peers": args.connect,
        "InterfacePeers": {},
        "Listen": args.listen,
        "AdminListen": "none",
        "MulticastInterfaces": [],
        "AllowedPublicKeys": [],
        "GroupPassword": "",
        "IfName": "auto",
        "IfMTU": 65535,
        "NodeInfoPrivacy": false,
        "NodeInfo": null
    }
    peer_ip: ipaddress.IPv6Address | None = None
    while True:
        try:
            await OneProcess(
                args,
                peer_ip,
                conf,
            ).main()
        except ChangedPeer as e:
            logging.info(repr(e))
            assert e.old == peer_ip
            peer_ip = e.new
        except Exception as e:
            logging.error('\n'+traceback.format_exc())
            # print(repr(e))
        await asyncio.sleep(0.1)


