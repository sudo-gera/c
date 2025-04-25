import ipaddress
import common
import asyncio
import sys

hosts : set[str] = set()
network = ipaddress.ip_network(sys.argv[1])
port = int(sys.argv[2])
hosts_count = int(sys.argv[3])


async def try_host(host: str) -> None:
    try:
        reader, writer = await asyncio.open_connection(host, port)
        hosts.add(host)
        await common.safe_socket_close(writer)
    except Exception as e:
        pass
        # print(e, type(e), file=sys.stderr)

async def find_hosts() -> None:
    while len(hosts) != hosts_count:
        # print('print hosts iteration', file=sys.stderr)
        await asyncio.sleep(0.3)
        for host in network:
            asyncio.create_task(try_host(str(host)))
        await asyncio.sleep(0.3)

async def main() -> None:
    await find_hosts()
    print(*hosts)

if __name__ == '__main__':
    asyncio.run(main())
