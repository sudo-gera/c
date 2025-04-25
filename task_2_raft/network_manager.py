import ipaddress
import common
import asyncio
import sys

hosts = sys.argv[1:]

'''
*filter
:INPUT ACCEPT [7:488]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [4:424]
-I INPUT -p tcp --dport 4444 -j DROP
-I OUTPUT -p tcp --sport 4444 -j DROP
COMMIT
'''

async def change_network_config() -> None:
    ...    

async def main() -> None:
    while 1:
        await asyncio.sleep(1)
        await change_network_config()

if __name__ == '__main__':
    asyncio.run(main())
