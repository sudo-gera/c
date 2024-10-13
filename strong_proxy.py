from __future__ import annotations
import asyncio
import argparse
import forwarding_parser
import stream
import sign
import random
from typing import *
import logging
import functools
import has_never_seen

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG)

args = argparse.Namespace()

signer = sign.Sign(8)
con_id_len = 8


class OuterConnection:
    def __new__(cls, con_id: bytes, gateway: stream.Stream | None, sock: stream.Stream | None = None) -> OuterConnection:
        if con_id not in outer_connections:
            outer_connections[con_id] = super().__new__(cls)
        self = outer_connections[con_id]
        return self
    def __init__(self, con_id: bytes, gateway: stream.Stream | None, sock: stream.Stream | None = None):
        self._awaiter = self._ainit(con_id, gateway, sock).__await__
    def __await__(self) -> Generator[Any, Any, OuterConnection]:
        return self._awaiter()
    async def _ainit(self, con_id: bytes, gateway: stream.Stream | None, sock: stream.Stream | None) -> OuterConnection:
        self.con_id = con_id
        if not hasattr(self, 'sock'):
            assert has_never_seen.has_never_seen(con_id)
            self.sock = stream.Stream(await asyncio.open_connection(*args.connect[0])) if sock is None else sock
            self.read_task = asyncio.create_task(self.reader_loop())
        if hasattr(self, 'gateway') and self.gateway is not None:
            await self.gateway.safe_close()
        self.gateway : stream.Stream | None = gateway
        return self
    async def reader_loop(self) -> None:
        try:
            async with self.sock:
                while (data := await self.sock.read(2**16)):
                    logger.debug(f'Got data to send inside: {data!r}')
                    while data is not None:
                        while self.gateway is None:
                            logger.debug(f'Waiting while holding: {data!r}')
                            await asyncio.sleep(0.1)
                        try:
                            await self.gateway.safe_write(data)
                            logger.debug(f'Successfully sent inside: {data!r}')
                            data = None
                        except Exception as e:
                            logger.debug(f'Send failed with: {data!r}, {type(e) = }, {e = }')
                            await self.gateway.safe_close()
                            self.gateway = None
        finally:
            del outer_connections[self.con_id]

outer_connections : dict[bytes, OuterConnection] = {} 

import types
types.coroutine

@stream.streamify
async def server_connection(sock: stream.Stream) -> None:
    con_id = signer.unsign(await sock.readexactly(con_id_len+signer.hash_len))
    logging.debug(f'inner client connected with {con_id.hex() = }')
    try:
        outer_connection = await OuterConnection(con_id, sock)
        logging.debug(f'sending good for  {con_id.hex() = }')
        await sock.safe_write(signer.sign(b'good'))
    except Exception:
        logging.debug(f'sending baad for  {con_id.hex() = }')
        await sock.safe_write(signer.sign(b'baad'))
        return
    try:
        while (data := await sock.read(2**16)):
            logger.debug(f'got data to send outside: {data!r}')
            await outer_connection.sock.safe_write(data)
            logger.debug(f'successfully send outside: {data!r}')
    except Exception as e:
        logger.debug(f'socket is closed: {data!r}, {type(e) = }, {e = }')
        outer_connection.gateway = None


@stream.streamify
async def client_connection(sock: stream.Stream) -> None:
    con_id = random.randbytes(con_id_len)
    logging.debug(f'outer client connected with {con_id.hex() = }')
    outer_connection = await OuterConnection(con_id, None, sock)
    while 1:
        try:
            async with stream.Stream(await asyncio.open_connection(*args.connect[0])) as sock:
                await sock.safe_write(signer.sign(con_id))
                status = signer.unsign(await sock.readexactly(4 + signer.hash_len))
                logging.debug(f'recv {status!r} for {outer_connection.con_id.hex() = }')
                if status != b'good':
                    return
                outer_connection.gateway = sock
                while (data := await sock.read(2**16)):
                    logger.debug(f'got data to send outside: {data!r}')
                    try:
                        await outer_connection.sock.safe_write(data)
                        logger.debug(f'successfully send outside: {data!r}')
                    except Exception as e:
                        logger.debug(f'outer socket is closed: {data!r}, {type(e) = }, {e = }')
                        return
        except Exception as e:
            outer_connection.gateway = None
            logger.debug(f'inner socket is closed, retrying: {con_id.hex() = } {type(e) = }, {e = }')
            pass
        await asyncio.sleep(0.1)


async def main() -> None:
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--is-server', action='store_true')
    args = parser.parse_args()
    async with await asyncio.start_server(server_connection if args.is_server else client_connection, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

