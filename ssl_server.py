import asyncio
import ssl

import stream


async def work(r, w):
    while 1:
        data = await r.read(2**16)
        print('got data:', data)
        w.write(data)
        await w.drain()

async def connection(r, w):
    print('connection started')
    async with stream.Stream(r, w) as s:
        async with stream.Stream(*await asyncio.open_connection('venus.web.telegram.org', 443, ssl=True)) as web:
            await asyncio.gather(work(s, web), work(web, s))
    print('connection stopped')

async def main():
    # con = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    # con.load_cert_chain(certfile='/Users/gera/localhost+2.pem', keyfile='/Users/gera/localhost+2-key.pem')
    server = await asyncio.start_server(connection, '0.0.0.0', 2000)#, ssl=con)
    async with server:
        await server.serve_forever()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass

