from udp_tcp import *

udp_clients = {}

async def tcp_connection(reader, writer):
    loop = asyncio.get_running_loop()
    async with stream.Stream(reader, writer) as tcp_connection:
        # asyncio.create_task(sender(tcp_connection))
        while 1:
            addr, data = await read_data(tcp_connection)
            if data is None:
                return
            if addr not in udp_clients:
                transport, protocol = await loop.create_datagram_endpoint(
                    lambda: udp_connection(tcp_connection, addr),
                    remote_addr=('127.0.0.1', 60002)
                )
                udp_clients[addr] = transport
            udp_clients[addr].sendto(data)

async def main():
    ser = await asyncio.start_server(tcp_connection, '127.0.0.1', 64001)
    async with ser:
        await ser.serve_forever()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
