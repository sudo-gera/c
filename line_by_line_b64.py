import asyncio
import sys
import base64

mode = sys.argv[1]

assert mode in ['encode', 'decode']

async def get_stdin_reader() -> asyncio.StreamReader:
    """
    Creates and returns an asyncio.StreamReader for sys.stdin.
    """
    stream_reader = asyncio.StreamReader()
    # StreamReaderProtocol acts as a bridge between the low-level transport/protocol API
    # and the high-level StreamReader API.
    protocol = asyncio.StreamReaderProtocol(stream_reader)
    loop = asyncio.get_running_loop()
    
    # Connect the standard input pipe to the event loop and protocol
    # The 'lambda: protocol' is a factory that the event loop uses to create the protocol instance.
    await loop.connect_read_pipe(lambda: protocol, sys.stdin)
    return stream_reader

stdin: asyncio.StreamReader

if mode == 'encode':
    async def encode_main() -> None:
        global stdin
        stdin = await get_stdin_reader()

        while (data := await stdin.read(60)):
            print(base64.b64encode(data).decode())

    asyncio.run(encode_main())
if mode == 'decode':
    async def encode_main() -> None:
        global stdin
        stdin = await get_stdin_reader()

        while (data := await stdin.readline()):
            sys.stdout.buffer.write(base64.b64decode(data))
            sys.stdout.flush()

    asyncio.run(encode_main())

