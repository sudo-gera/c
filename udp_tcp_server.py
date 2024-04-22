import asyncio
from udp_tcp import *

udp_clients = {}

async def main() -> None:
    loop = asyncio.get_running_loop()
    transport, protocol = await loop.create_datagram_endpoint(lambda: udp_connection(tcp_connection), local_addr=('127.0.0.1', 60002))
    rw = await asyncio.open_connection('127.0.0.1', 64001)
    assert isinstance(transport, asyncio.BaseTransport)
    udp_clients[None] = transport
    await tcp_connection(*rw, False)


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
