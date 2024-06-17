import asyncio
import stream

async def test():
    try:
        await asyncio.sleep(1)
    except BaseException as e:
        print(type(e), e)

async def main():
    try:
        asyncio.create_task(test())
        asyncio.create_task(test())
        asyncio.create_task(test())
        async with stream.Stream(*await asyncio.open_connection('127.0.0.1',3322)) as sock:
            print(await sock.read())

    except BaseException as e:
        print(e)


asyncio.run(main())