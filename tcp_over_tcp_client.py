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
    reconnect_interval: float
    log_level: LogLevelEnum

@dataclass
class context:
    args: main_args
    transports: tcp_over_tcp_transport.ConnectedTransports
    ctx: tcp_over_tcp_common.context

async def start_transport(ctx: context) -> None:
    while True:
        try:
            reader, writer = await asyncio.open_connection(ctx.args.tcp_connect_host, ctx.args.tcp_connect_port)
            try:
                logging.info(f"Transport connected")
                await ctx.transports.no_owning_connect(reader, writer)
            finally:
                writer.close()
                await writer.wait_closed()
                logging.info(f"Transport closed")
        except Exception as e:
            logging.warning(f"Transport error: {e!r}")
        await asyncio.sleep(ctx.args.reconnect_interval)

async def on_client_connect(ctx: context, reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    conn = tcp_over_tcp_common.connection(
        uuid.uuid4(),
        ctx.transports.wrapped,
        reader,
        writer,
        ctx.ctx,
    )
    logging.info(f"Client accepted: {conn.connection_id = }")
    await conn.conn_loop()

@dataclass
class NewConnectionHandler(tcp_over_tcp_common.INewConnectionHandler):
    ctx: context

    async def handle_new_connection(self, transport: tcp_over_tcp_transport.ITransport, connection_id: uuid.UUID) -> tcp_over_tcp_common.connection | None:
        logging.warning(f"Ignoring data for {connection_id = !r}")
        return None

async def start_server(ctx: context) -> None:

    async with await asyncio.start_server(
        lambda reader, writer: fire(on_client_connect(ctx, reader, writer)),
        ctx.args.tcp_listen_host,
        ctx.args.tcp_listen_port,
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
    transports = tcp_over_tcp_transport.ConnectedTransports(conf)

    ctx = context(
        args,
        transports,
        tcp_over_tcp_common.context(),
    )

    await wait_until_all_complete_or_cancel_on_exc(
        tcp_over_tcp_common.route_incoming_messages(
            ctx.ctx,
            ctx.transports.wrapped,
            NewConnectionHandler(ctx),
        ),
        start_server(ctx),
        start_transport(ctx),
    )


if_main_parse_args_and_asyncio_run(__name__, main)






