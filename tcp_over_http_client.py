from __future__ import annotations

import argparse
import asyncio
import aiohttp
import uuid

parser = argparse.ArgumentParser()
parser.add_argument("--http-url", type=str, required=True)
parser.add_argument("--tcp-host",  type=str, required=True)
parser.add_argument("--tcp-port",  type=int, required=True)
args = parser.parse_args()

http_url = args.http_url
assert isinstance(http_url, str)
tcp_host = args.tcp_host
assert isinstance(tcp_host, str)
tcp_port = args.tcp_port
assert isinstance(tcp_port, int)

async def handle_client(
    reader: asyncio.StreamReader,
    writer: asyncio.StreamWriter,
    session: aiohttp.ClientSession,
) -> None:
    sid = uuid.uuid4().hex

    try:

        async with session.post(f"{http_url}/open", params={"id": sid}, data=b"") as resp:
            pass

        async def tcp_to_http() -> None:
            while True:
                data = await reader.read(4096)

                async with session.post(f"{http_url}/send", params={"id": sid}, data=data) as resp:
                    pass
                
                if not data:
                    break

        async def http_to_tcp() -> None:
            while True:
                async with session.get(
                    f"{http_url}/recv",
                    params={"id": sid},
                ) as resp:

                    data = await resp.read()

                writer.write(data)
                await writer.drain()

                if not data:
                    writer.write_eof()
                    break

        await asyncio.gather(tcp_to_http(), http_to_tcp())

    finally:
        writer.close()
        await writer.wait_closed()


async def main() -> None:

    async with aiohttp.ClientSession() as session:
        server = await asyncio.start_server(
            lambda r, w: handle_client(r, w, session),
            tcp_host,
            tcp_port,
        )

        async with server:
            await server.serve_forever()


if __name__ == "__main__":
    asyncio.run(main())
