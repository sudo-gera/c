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

from tcp_over_tcp_useful_tools import wait_until_all_complete_or_cancel_on_exc, uuid_bytes_size, terminate

############################################################################################################################

# Do not expose this app to untrusted network.
# This file is not a security layer.
# Authentication and encryption must be handled on other layers.

import tcp_over_tcp_transport

@dataclass
class connection:
    connection_id: uuid.UUID
    transport: tcp_over_tcp_transport.ITransport
    reader: asyncio.StreamReader
    writer: asyncio.StreamWriter
    ctx: context
    
    queue: asyncio.Queue[bytes|None] = field(default_factory=lambda: asyncio.Queue(maxsize=8))

    async def write_message(self, data: bytes | int) -> None:
        if isinstance(data, int):
            if data == 0:
                terminate(f"data cannot be 0")
            await self.transport.write(self.connection_id.bytes + data.to_bytes(1, 'big'))
        else:
            await self.transport.write(self.connection_id.bytes + b'\x00' + data)

    async def conn_loop(self) -> None:
        try:
            try:
                self.ctx.routes[self.connection_id] = self
                try:
                    await self.write_message(2)

                    async def to_transport() -> None:
                        while (data := await self.reader.read(2**16)):
                            await self.write_message(data)
                        await self.write_message(1)

                    async def from_transport() -> None:
                        while (data := await self.queue.get()) is not None:
                            self.writer.write(data)
                            await self.writer.drain()
                        if self.writer.can_write_eof():
                            self.writer.write_eof()

                    # Wait for latter result or first error.
                    # In case of half-duplex connection,
                    # one loop stops and we wait for other one.
                    await wait_until_all_complete_or_cancel_on_exc(
                        to_transport(),
                        from_transport(),
                    )
                finally:
                    self.ctx.routes.pop(self.connection_id, None)
            finally:
                self.writer.close()
                await self.writer.wait_closed()
        except Exception as e:
            logging.warning(f"Transport error: {e!r}")
        finally:
            logging.info(f"Client closed: {self.connection_id = }")
        

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
        connection_id, msgtype, data = uuid.UUID(bytes=data[:uuid_bytes_size]), data[uuid_bytes_size:uuid_bytes_size+1], data[uuid_bytes_size+1:]
        conn = ctx.routes.get(connection_id, None)
        if conn is None and msgtype == b'\x02':
            conn = await new_conn_handler.handle_new_connection(transport, connection_id)
        if conn is None:
            logging.warning(f"Client {connection_id = } does not exist.")
            continue
        if msgtype == b'\x01':
            await conn.queue.put(None)
        else:
            await conn.queue.put(data)                


