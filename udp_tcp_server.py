from udp_tcp import *

async def main():
    loop = asyncio.get_running_loop()
    try:
        async with stream.Stream(*await asyncio.open_connection('127.0.0.1', 64001)) as tcp_connection:
            asyncio.create_task(sender(tcp_connection))
            transport, protocol = await loop.create_datagram_endpoint(lambda: udp_connection(tcp_connection), local_addr=('127.0.0.1', 60002))
            while 1:
                try:
                    message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
                except asyncio.IncompleteReadError:
                    return
                data, addr = json.loads(message)
                data = base64.b64decode(data)
                addr = tuple(addr)
                transport.sendto(data, addr)
    finally:
        transport.close()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
