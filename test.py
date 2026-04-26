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

############################################################################################################################

logger = logging.getLogger(__name__)

class always_upper_str(str):
    def __new__(cls, *args: Any, **kwargs: Any) -> always_upper_str:
        return super().__new__(cls,
            super().__new__(cls, *args, **kwargs).upper()
        )

logging_levels = [
    'info', 111
]

class LogLevelEnumMeta(EnumMeta):
    def __new__(mcs: Any, name: Any, bases: Any, attrs: Any) -> Any:
        attrs_to_add = {    'info': 111}
        print(attrs_to_add)
        print(attrs)
        attrs |= attrs_to_add
        print(attrs)
        return super().__new__(mcs, name, bases, attrs)

class LogLevelEnum(Enum, metaclass=LogLevelEnumMeta):
    pass

print(LogLevelEnum.info)
exit()
