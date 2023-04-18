import asyncio
import random

class connection(asyncio.Protocol):
    def connection_made(self, transport):
        peername = transport.get_extra_info('peername')
        print('Connection from {}'.format(peername))
        self.transport = transport

    def data_received(self, data):
        asyncio.create_task(self.dr(data))

    async def dr(self,data):
        message = data.decode()
        print('Data received: {!r}'.format(message))

        await asyncio.sleep(random.random())

        print('_________Send: {!r}'.format(message))
        self.transport.write(data)

        print('Close the client socket')
        self.transport.close()


async def main():
    loop = asyncio.get_running_loop()
    server = await loop.create_server(
        connection,
        '',8787)
    async with server:
        await server.serve_forever()
    await asyncio.gather(*asyncio.all_tasks() - {asyncio.current_task()})
asyncio.run(main())

