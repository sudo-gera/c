import ipaddress
import common
import asyncio
import sys
import time
import psutil
import traceback
import logging
import typing

##############################################################################################################################################

hosts = sys.argv[1:]
hosts.sort()
my_ip = common.select_my_ip(hosts)
other_hosts = {*hosts} - {my_ip}

##############################################################################################################################################

colors = [
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
    '\x1b[97m',
]
my_color = colors[hosts.index(my_ip)]
clear_color = '\x1b[0m'

##############################################################################################################################################

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format=my_color +'[  ' + (my_ip + ' '*20)[:12] + ' ] [ %(asctime)s ]: %(message)s' + clear_color)

class log_stream:
    def __init__(self, logger_func: typing.Callable[[str], None]):
        self.logger_func = logger_func
        self.buffer = ''
    def write(self, data: str) -> None:
        self.buffer += data
        while '\n' in self.buffer:
            data, self.buffer = self.buffer.split('\n', 1)
            self.logger_func(data)
            sys.stdout.flush()
            sys.stderr.flush()

debug_stream = log_stream(logging.debug)
info_stream = log_stream(logging.info)
error_stream = log_stream(logging.error)

##############################################################################################################################################

async def on_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    try:
        host = writer.get_extra_info('peername')[0]
        print('got connection from', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
    finally:
        await common.safe_socket_close(writer)

async def listening_server() -> None:
    try:
        async with await asyncio.start_server(on_connection, '0.0.0.0', 4444) as server:
            await server.serve_forever()
    except:
        print(traceback.format_exc(), file=error_stream)

async def ping_one_host(host:str) -> None:
    try:
        reader, writer = await common.run_with_timeout(asyncio.open_connection(host, 4444), 1)
        try:
            print('connected to', colors[hosts.index(host)]+host+clear_color, file=debug_stream)
        finally:
            await common.safe_socket_close(writer)
    except Exception:
        pass

async def pinger() -> None:
    while 1:
        await asyncio.sleep(1)
        await asyncio.gather(*map(ping_one_host, other_hosts))

async def main() -> None:
    await asyncio.gather(
        pinger(),
        listening_server(),
    )

if __name__ == '__main__':
    asyncio.run(main())


