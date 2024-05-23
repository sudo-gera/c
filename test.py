import asyncio
import os
import random
import sys

async def test(i):
    reader, writer = await asyncio.open_connection('127.0.0.1', 9999)
    one_message = b'get hash '+os.path.abspath(__file__).encode()
    multimessage = b'\n'.join([one_message] * random.randint(20, 30)) # join several requests
    while multimessage:
        chunk = multimessage[:random.randint(1, len(multimessage))] # split into chunks of random length
        multimessage = multimessage[len(chunk):]
        writer.write(multimessage)
        await writer.drain()
    writer.write_eof()
    await writer.drain()
    await reader.read()
    writer.close()
    await writer.wait_closed()

async def main():
    process = await asyncio.create_subprocess_exec(sys.argv[1], '9999')
    await asyncio.sleep(1)
    await asyncio.gather(*map(test, range(99)))
    reader, writer = await asyncio.open_connection('127.0.0.1', 9999)
    writer.write(b'quit')
    writer.write_eof()
    await writer.drain()
    await reader.read()
    writer.close()
    await writer.wait_closed()

asyncio.run(main())
