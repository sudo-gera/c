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
import abc
import zlib
import heapq

############################################################################################################################

from tcp_over_tcp_useful_tools import wait_until_all_complete_or_cancel_on_exc, uuid_bytes_size

############################################################################################################################

# Do not expose this app to untrusted network.
# This file is not a security layer.
# Authentication and encryption must be handled on other layers.

import tcp_over_tcp_transport

@dataclass
class connection:
    connection_id: uuid.UUID
    transport: tcp_over_tcp_transport.ITransport
    queue: asyncio.Queue[bytes] = field(default_factory=asyncio.Queue)

    async def write_message(self, data: bytes) -> None:
        await self.transport.write(self.connection_id.bytes + data)

    async def conn_route_loop(self, ctx: context, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:

        # While ITransport supports sending b'' as separate message,
        # TCP does not and never will.
        # In TCP b'' always means EOF.
        # So we can send b'' to other end to mean EOF.

        async def to_transport() -> None:
            while (data := await reader.read(2**16)):
                await self.write_message(data)
            await self.write_message(data)

        async def from_transport() -> None:
            while (data := await self.queue.get()):
                writer.write(data)
                await writer.drain()
            if writer.can_write_eof():
                writer.write_eof()

        # Wait for latter result or first error.
        # In case of half-duplex connection,
        # one loop stops and we wait for other one.
        await wait_until_all_complete_or_cancel_on_exc(
            to_transport(),
            from_transport(),
        )

@dataclass
class context:
    routes: dict[uuid.UUID, connection] = field(default_factory=dict)

class INewConnectionHandler(abc.ABC):
    
    @abc.abstractmethod
    async def handle_new_connection(self, transport: tcp_over_tcp_transport.ITransport, connection_id: uuid.UUID) -> connection | None:
        ...

async def route_incoming_messages(ctx: context, transport: tcp_over_tcp_transport.ITransport, new_conn_handler: INewConnectionHandler) -> None:

    while True:
        data = await transport.read()
        if len(data) < uuid_bytes_size:
            raise ValueError(f"Got small chunk: {data = !r}")
        connection_id, data = uuid.UUID(bytes=data[:uuid_bytes_size]), data[uuid_bytes_size:]
        conn = ctx.routes.get(connection_id, None)
        if conn is None:
            conn = await new_conn_handler.handle_new_connection(transport, connection_id)
        if conn is None:
            continue
        ctx.routes[connection_id].queue.put_nowait(data)

