import ipaddress
import common
import asyncio
import sys
import time
import psutil

hosts = sys.argv[1:]

my_ip = common.select_my_ip(hosts)

async def main() -> None:
    while 1:
        await asyncio.sleep(1)
        print(my_ip, time.asctime())

if __name__ == '__main__':
    asyncio.run(main())


