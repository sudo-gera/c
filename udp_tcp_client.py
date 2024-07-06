import stream
import asyncio
from udp_tcp import *


udps : dict[addr_type, udp_connection] = {}

async def get_udp(key_addr: addr_type) -> tuple[udp_connection, addr_type]:
    if key_addr not in udps:
        loop = asyncio.get_running_loop()
        transport, protocol = await loop.create_datagram_endpoint(
            lambda: udp_connection(key_addr),
            remote_addr=args().udp
        )
        udps[key_addr] = protocol
    return udps[key_addr], args().udp


async def main() -> None:
    server = await asyncio.start_server(lambda r,w: connection_loop(r, w, get_udp), *args().tcp)
    async with server:
        await server.serve_forever()
    

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass

