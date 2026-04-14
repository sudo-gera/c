import asyncio
import json
import argparse
import io
import base64
import sys
import subprocess
import pickle
import time
from functools import partial
import traceback
from typing import *

def log(*a: Any, **s: Any) -> None:
    pass
    # print(*a, **s)

async def read_chunk(reader: asyncio.StreamReader) -> bytes:
    l = await reader.readline()
    if not l:
        raise EOFError
    return await reader.readexactly(int(l))

async def write_chunk(writer: asyncio.StreamWriter, data: bytes) -> None:
    writer.write(str(len(data)).encode() + b'\n' + data)
    await writer.drain()

async def read_pickle(reader: asyncio.StreamReader) -> Any:
    return pickle.loads(await read_chunk(reader))

async def write_pickle(writer: asyncio.StreamWriter, data: Any) -> None:
    await write_chunk(writer, pickle.dumps(data))

def write_data_to_object(name: str, data: bytes, obj: Any) -> None:
    writer = getattr(obj, name)
    log('> decoding', data, name)
    if isinstance(writer, asyncio.StreamWriter):
        if data:
            writer.write(data)
        else:
            writer.write_eof()
            log('> finished decoding', name)
    else:
        writer.buffer.write(data)
        writer.flush()

to_call_on_close : list[Callable[[], Any]] = []

def exit_to_object(code: int, obj: Any) -> None:
    log('> closing connection')
    for a in to_call_on_close:
        a()

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

async def encode_stream(reader: asyncio.StreamReader, name: str, writer: Any) -> None:
    while 1:
        data = await reader.read(2**16)
        log('> encoding', data, name)
        await write_pickle(writer, partial(write_data_to_object, name, data))
        if not data:
            break
    log('> finished encoding', name)

async def decode_stream(reader: asyncio.StreamReader, obj: Any) -> None:
    while 1:
        try:
            handler = await read_pickle(reader)
        except EOFError:
            break
        handler(obj)
    log('> finished decoding')

async def wait(process: asyncio.subprocess.Process, writer: asyncio.StreamWriter) -> None:
    code = await process.wait()
    log('> closing connection')
    await write_pickle(writer, partial(exit_to_object, code))

async def alive_checker() -> None:
    file=sys.stderr
    while 1:
        print('\x1b[s\r\x1b[160C' + f'{time.time_ns():,}' + '\x1b[u', end='', file=file)
        file.flush()
        await asyncio.sleep(0.1)

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        command = cast(list[str], await read_pickle(reader))
        params = cast(str, await read_pickle(reader))
        try:
            process = await asyncio.create_subprocess_exec(*command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, **json.loads(params))
            stdout = process.stdout
            assert stdout is not None
            stderr = process.stderr
            assert stderr is not None
            try:
                await asyncio.gather(
                    encode_stream(stdout, 'stdout', writer),
                    encode_stream(stderr, 'stderr', writer),
                    decode_stream(reader, process),
                    wait(process, writer)
                )
                log('> after gather')
            finally:
                try:
                    process.terminate()
                except ProcessLookupError:
                    pass
        except Exception:
            try:
                await write_pickle(writer, partial(write_data_to_object, 'stderr', traceback.format_exc().encode()))
            except Exception:
                print(traceback.format_exc(), file=sys.stderr)
            raise
    finally:
        writer.close()
        await writer.wait_closed()


async def connect(reader: asyncio.StreamReader, writer: asyncio.StreamWriter, command: list[str], params: str) -> None:
    try:
        await write_pickle(writer, command)
        await write_pickle(writer, params)
        stdin_task = asyncio.create_task(encode_stream(await get_stdin_reader(), 'stdin', writer))
        await asyncio.gather(
            decode_stream(reader, sys),
        )
        log('> after gather')
    finally:
        writer.close()
        await writer.wait_closed()

async def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--host', type=str, required=True)
    parser.add_argument('--port', type=int, required=True)
    parser.add_argument('--params', type=str, default='{}')
    parser.add_argument('command', type=str, nargs='*')
    args = parser.parse_args()
    host = cast(str, args.host)
    port = cast(int | None, args.port)
    command = cast(list[str] | None, args.command)
    params = cast(str, args.params)
    json.loads(params)
    if command:
        reader, writer = await asyncio.open_connection(host, port)
        to_call_on_close.append(writer.write_eof)
        await connect(reader, writer, command, params)
    else:
        server = await asyncio.start_server(on_connection, host, port)
        async with server:
            await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
