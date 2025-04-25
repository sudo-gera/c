import ipaddress
import common
import asyncio
import sys

hosts : list[str] = []
network = ipaddress.ip_network(sys.argv[1])
port = int(sys.argv[2])
hosts_count = int(sys.argv[3])


async def try_host(host: str):
    try:
        reader, writer = await asyncio.open_connection(host, port)
        hosts.append(host)
        await common.safe_socket_close(writer)
    except Exception:
        pass

async def find_hosts():
    while len(hosts) != hosts_count:
        await asyncio.sleep(0.1)
        for host in network:
            asyncio.create_task(try_host(host))
        await asyncio.sleep(0.1)

async def main():
    await find_hosts()
    print(*hosts)

if __name__ == '__main__':
    asyncio.run(main())
