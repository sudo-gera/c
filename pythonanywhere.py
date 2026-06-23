import asyncio
from websockets.asyncio.client import connect, ClientConnection

recv_queue: asyncio.Queue[str | bytes] = asyncio.Queue(maxsize=64)

async def recv_into_queue(ws: ClientConnection) -> None:
    while 1:
        chunk = await ws.recv()
        await recv_queue.put(chunk)

recver : asyncio.Task[None] | None = None

async def open_pythonanywhere_websocket(ws_url: str, first_ws_message: str) -> ClientConnection:
    ws = await connect(
        ws_url,
        origin="https://www.pythonanywhere.com",
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
    await asyncio.sleep(8)
    while not recv_queue.empty():
        recv_queue.get_nowait()
    return ws
    
async def main(ws_url: str, first_ws_message: str):
    ws = await open_pythonanywhere_websocket(ws_url, first_ws_message)

    await ws.send('["curl -LO \'https://raw.githubusercontent.com/sudo-gera/c/b1a7b219005614bfb4cb75d2a088be43055e4c5a/raw_input.py\' ; python3 raw_input.py \\n"]')

    await asyncio.Future()

    await ws.close()


import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--ws-url', required=True)
parser.add_argument('--first-ws-message', required=True)
args = parser.parse_args()

asyncio.run(main(args.ws_url, args.first_ws_message))
