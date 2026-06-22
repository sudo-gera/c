import asyncio
from websockets.asyncio.client import connect, ClientConnection

recv_queue: asyncio.Queue[str | bytes] = asyncio.Queue(maxsize=64)

async def recv_into_queue(ws: ClientConnection) -> None:
    while 1:
        chunk = await ws.recv()
        await recv_queue.put(chunk)

async def open_pythonanywhere_websocket(ws_url: str, first_ws_message: str) -> ClientConnection:
    ws = await connect(
        # "wss://consoles-12.pythonanywhere.com/sj/887/f3x5zvu_/websocket",
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
    await ws.send(first_ws_message)
    
async def main():
    ws = await open_pythonanywhere_websocket()

    print(await ws.recv())

    await ws.send('["\\u001b[asv0x1m98qlf4fd6q9xzafcdorhv62ry;45454587;;a"]')

    t = asyncio.create_task(recver(ws))

    await asyncio.sleep(8)

    await ws.send('["pwd\\ns"]')

    await asyncio.Future()

    await ws.close()


import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--ws-url')
parser.add_argument('--first-ws-message')


asyncio.run(main())
