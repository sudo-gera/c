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

async def main():
    async with await asyncio.start_server(command_handler, '0.0.0.0', 2100) as server:
        server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())
