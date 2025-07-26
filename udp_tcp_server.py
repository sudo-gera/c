from udp_tcp import *
import traceback

import asyncio
import stream
import functools


async def main() -> None:
    loop = asyncio.get_running_loop()
    transport, protocol = await loop.create_datagram_endpoint(udp_connection, local_addr=args().udp)
    async def get_udp(key_addr: addr_type) -> tuple[udp_connection, addr_type]:
        return protocol, key_addr
    try:
        while 1:
            try:
                rw = await asyncio.open_connection(*args().tcp)
            except (ConnectionRefusedError, OSError):
                continue
            await connection_loop(*rw, get_udp)
            await asyncio.sleep(1)
    finally:
        transport.close()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
