from __future__ import annotations
import asyncio
import argparse
import forwarding_parser
import stream
import sign
import random

signer = sign.Sign(8)
con_id_len = 256

class OuterConnection:
    def __new__(cls, con_id: bytes, gateway: stream.Stream, sock: stream.Stream ):
        if con_id not in outer_connections:
            outer_connections[con_id] = super().__new__(cls)
        self = outer_connections[con_id]
        self.__await__ = self._ainit(con_id, gateway).__await__
        return self
    async def _ainit(self, con_id: bytes, gateway: stream.Stream) -> OuterConnection:
        self.con_id = con_id
        if not hasattr(self, 'sock'):
            self.sock = stream.Stream(await asyncio.open_connection(*args.connect[0]))
            self.read_task = asyncio.create_task(self.reader_loop)
        if hasattr(self, 'gateway') and self.gateway is not None:
            await self.gateway.safe_close()
        self.gateway : stream.Stream | None = gateway
        return self
    async def reader_loop(self):
        async with self.sock:
            while (data := self.sock.read(2**16)):
                while data is not None:
                    while self.gateway is None:
                        await asyncio.sleep(0.1)
                    try:
                        await self.gateway.safe_write(data)
                        data = None
                    except Exception:
                        await self.gateway.safe_close()
                        self.gateway = None

outer_connections : dict[bytes, OuterConnection] = {} 

import types
types.coroutine

@stream.streamify
async def server_connection(sock: stream.Stream):
    outer_connection = await OuterConnection(
        con_id = signer.unsign(
            await sock.readexactly(con_id_len + signer.hash_len)
        ),
        gateway = sock,
    )
    while (data := sock.read(2**16)):
        await outer_connection.sock.safe_write(data)


@stream.streamify
async def client_connection(sock: stream.Stream):
    gateway = stream.Stream(await asyncio.open_connection(*args.connect[0]))
    outer_connection = await OuterConnection(random.randbytes(signer.hash_len), gateway)



async def main():
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--interval', type=int, default=None)
    args = parser.parse_args()
    async with await asyncio.start_server(server_connection if args.interval is None else client_connection, *args.listen[0]) as server:
        server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())

