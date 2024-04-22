import asyncio
from udp_tcp import *

udp_clients = {}

async def main() -> None:
    loop = asyncio.get_running_loop()
    rw = await asyncio.open_connection('127.0.0.1', 64001)
    await tcp_connection(*rw, False)


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
