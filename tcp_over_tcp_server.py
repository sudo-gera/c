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

from tcp_over_tcp_useful_tools import LogLevelEnum, fire, set_log_level, wait_until_all_complete_or_cancel_on_exc, if_main_parse_args_and_asyncio_run

############################################################################################################################

# This file is not a security layer.
# Authentication and encryption must be handled on other layers.

import tcp_over_tcp_common
import tcp_over_tcp_transport

@dataclass(frozen=True)
class main_args(tcp_over_tcp_transport.Config):
    tcp_listen_host: str
    tcp_listen_port: int
    tcp_connect_host: str
    tcp_connect_port: int
    log_level: LogLevelEnum

@dataclass
class context:
    args: main_args
    transports: tcp_over_tcp_transport.AcceptedTransports
    ctx: tcp_over_tcp_common.context

@dataclass
class NewConnectionHandler(tcp_over_tcp_common.INewConnectionHandler):
    ctx: context

    async def create_connection(self, conn: tcp_over_tcp_common.connection) -> None:
        try:
            reader, writer = await asyncio.open_connection(self.ctx.args.tcp_connect_host, self.ctx.args.tcp_connect_port)
            try:
                logging.info(f"Client connected: {conn.connection_id = }")

                await conn.conn_route_loop(self.ctx.ctx, reader, writer)

            finally:
                self.ctx.ctx.routes.pop(conn.connection_id, None)
                writer.close()
                await writer.wait_closed()
                logging.info(f"Client closed: {conn.connection_id = }")
        except Exception as e:
            logging.warning(f"Client error: {e!r}")

    async def handle_new_connection(self, transport: tcp_over_tcp_transport.ITransport, connection_id: uuid.UUID) -> tcp_over_tcp_common.connection | None:
        conn = tcp_over_tcp_common.connection(
            connection_id,
            transport,
        )
        self.ctx.ctx.routes[conn.connection_id] = conn
        fire(self.create_connection(conn))
        return conn

async def on_connect(ctx: context, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        try:
            logging.info(f"Transport accepted")

            await ctx.transports.no_owning_accept(reader, writer)
        finally:
            writer.close()
            await writer.wait_closed()
            logging.info(f"Transport closed")
    except Exception as e:
        logging.warning(f"Transport error: {e!r}")

async def start_server(ctx: context) -> None:

    async with await asyncio.start_server(
        lambda reader, writer: fire(on_connect(ctx, reader, writer)),
        ctx.args.tcp_listen_host,
        ctx.args.tcp_listen_port
    ) as server:
        await server.serve_forever()

async def main(args: main_args) -> None:

    set_log_level(args.log_level)

    conf = tcp_over_tcp_transport.Config(
        alive_interval = args.alive_interval,
        max_missing_alives = args.max_missing_alives,
        cache_chunks = args.cache_chunks,
        max_chunk_size = args.max_chunk_size,
        resend_interval = args.resend_interval,
        disable_authentication = args.disable_authentication,
        disable_encryption = args.disable_encryption,
    )

    ctx = context(
        args,
        cast(tcp_over_tcp_transport.AcceptedTransports, ...),
        tcp_over_tcp_common.context(),
    )

    transports = tcp_over_tcp_transport.AcceptedTransports(
        conf,
        lambda transport: fire(
            tcp_over_tcp_common.route_incoming_messages(
                ctx.ctx,
                transport,
                NewConnectionHandler(ctx),
            )
        ),
    )

    ctx.transports = transports

    await wait_until_all_complete_or_cancel_on_exc(
        start_server(ctx),
    )

if_main_parse_args_and_asyncio_run(__name__, main)






