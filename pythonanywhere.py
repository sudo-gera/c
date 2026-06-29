from typing import *
import asyncio
import json
import typing
from websockets.asyncio.client import connect, ClientConnection
import websockets.exceptions

tasks : set[asyncio.Task[None]] = set()

def fire(coro: typing.Awaitable[Any]) -> None:
    async def wrapper() -> None:
        try:
            await coro
        except asyncio.CancelledError:
            pass
        except BaseException:
            raise KeyboardInterrupt

    task : asyncio.Task[Any] = asyncio.create_task(wrapper())
    tasks.add(task)
    task.add_done_callback(tasks.discard)

recv_queue: asyncio.Queue[str | bytes] = asyncio.Queue(maxsize=64)

async def recv_into_queue(ws: ClientConnection) -> None:
    while 1:
        try:
            chunk = await ws.recv()
        except websockets.exceptions.ConnectionClosedOK:
            break
        else:
            await recv_queue.put(chunk)

def flush_recv_queue() -> None:
    while not recv_queue.empty():
        recv_queue.get_nowait()

async def wait_and_flush_recv_queue(delay: float) -> None:
    await asyncio.sleep(delay)
    flush_recv_queue()

recver : asyncio.Task[None] | None = None

async def open_pythonanywhere_websocket(ws_url: str, first_ws_message: str) -> ClientConnection:
    ws = await connect(
        ws_url,
        origin=cast(None, "https://www.pythonanywhere.com"),
        additional_headers={
            "Sec-GPC": "1",
            "Cache-Control": "no-cache",
            "Accept-Language": "en-US,en;q=0.9",
            "Pragma": "no-cache",
            "User-Agent": (
                "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                "Chrome/147.0.0.0 Safari/537.36"
                "AppleWebKit/537.36 (KHTML, like Gecko) "
            ),
        },
    )
    global recver
    recver = asyncio.create_task(recv_into_queue(ws))
    await ws.send(first_ws_message)
    return ws
    
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

async def reader_to_ws(reader: asyncio.StreamReader, ws: ClientConnection) -> None:
    while (data := await reader.read(2**64)):
        await ws.send(json.dumps([data.decode()]))

async def recv_into_stream(ws: ClientConnection, stream: IO[str]) -> None:
    while 1:
        data_ = await recv_queue.get()
        if isinstance(data_, bytes):
            data = data_.decode()
        else:
            data = data_
        if data[0] == 'a':
            data = data[1:]
            objs = json.loads(data)
            if isinstance(objs, list):
                for obj in objs:
                    if isinstance(obj, str):
                        stream.write(obj)
                        stream.flush()

async def main(ws_url: str, first_ws_message: str, commit_hash: str) -> None:
    stdin = await get_stdin_reader()

    ws = await open_pythonanywhere_websocket(ws_url, first_ws_message)
    try:
        n='\n'
        await ws.send(json.dumps([
            f'\x03'
        ]))

        await asyncio.sleep(1)

        await ws.send(json.dumps([
            f"curl -sSLO https://raw.githubusercontent.com/sudo-gera/c/{commit_hash}/raw_input.py ; "
            f"curl -sSLO https://raw.githubusercontent.com/sudo-gera/c/{commit_hash}/line_by_line_b64.py ; "
            f"clear ; sleep 2 ; "
            f"python3 line_by_line_b64.py decode '>>> ' | nc 127.0.0.1 22 | python3 line_by_line_b64.py encode '<<< ' ; "
            f"\n"
        ]))

        await wait_and_flush_recv_queue(2)

        fire(recv_into_stream(ws, sys.stdout))

        await reader_to_ws(stdin, ws)
    finally:
        await ws.close()


import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--ws-url', required=True)
parser.add_argument('--first-ws-message', required=True)
parser.add_argument('--commit-hash', required=True)
args = parser.parse_args()

asyncio.run(main(args.ws_url, args.first_ws_message, args.commit_hash))
