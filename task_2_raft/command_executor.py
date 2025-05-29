import asyncio
import io
import subprocess

import common

addr : str

async def command_handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        command = await reader.read()
        if not command:
            return
        process = await asyncio.create_subprocess_shell(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        process_closed = False
        try:
            stdout, stderr = await process.communicate()
            process_closed = True
        finally:
            if not process_closed:
                process.terminate()
            await process.wait()
        writer.write(stdout)
        writer.write(stderr)
        await writer.drain()
    finally:
        await common.safe_socket_close(writer)

async def main() -> None:
    async with await asyncio.start_server(command_handler, '0.0.0.0', 2100) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())
