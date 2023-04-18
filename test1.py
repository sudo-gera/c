import aiohttp
import asyncio
import random
async def connect(session):
    a=str(random.random())
    async with session.get('http://localhost:8089/'+a) as resp:
        assert a==await resp.text()
    

async def main():
    async with aiohttp.ClientSession() as session:
        for q in range(999):
            asyncio.create_task(connect(session))
        await asyncio.gather(*asyncio.all_tasks() - {asyncio.current_task()})


asyncio.run(main())