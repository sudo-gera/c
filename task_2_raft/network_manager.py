import ipaddress
import common
import asyncio
import sys

hosts = sys.argv[1:]

async def change_network_config():
    ...

async def main():
    while 1:
        await asyncio.sleep(1)
        await change_network_config()

if __name__ == '__main__':
    asyncio.run(main())
