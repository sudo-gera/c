from udp_tcp import *

async def main():
    ser = await asyncio.start_server(tcp_connection, '127.0.0.1', 64001)
    async with ser:
        await ser.serve_forever()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
