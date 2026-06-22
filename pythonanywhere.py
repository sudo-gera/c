import asyncio
import websockets
import websockets.asyncio
from websockets.asyncio.client import connect


async def open_pythonanywhere_websocket():
    return await connect(
        "wss://consoles-12.pythonanywhere.com/sj/887/f3x5zvu_/websocket",
        origin="https://www.pythonanywhere.com",
        additional_headers={
            "Sec-GPC": "1",
            "Cache-Control": "no-cache",
            "Accept-Language": "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7",
            "Pragma": "no-cache",
            "User-Agent": (
                "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/147.0.0.0 Safari/537.36"
            ),
        },
    )


async def main():
    ws = await open_pythonanywhere_websocket()

    await ws.send("hello")
    response = await ws.recv()
    print(response)

    await ws.close()


asyncio.run(main())
