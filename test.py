import asyncio
class test:
    def __await__(self):
        return asyncio.sleep(1).__await__()
    
async def main():
    print(await test())

asyncio.run(main())
