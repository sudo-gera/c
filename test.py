import asyncio

async def ex():
    await asyncio.sleep(1)
    print('exiting')
    exit()


async def main():
    asyncio.create_task(ex())
    await asyncio.sleep(2)
    print('not exited')

asyncio.run(main())
