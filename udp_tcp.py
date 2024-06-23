import asyncio
import json
import base64
import stream
import argparse
import typing
import collections.abc
import re
import time
import timeout

addr_type = tuple[str, int]
messages : asyncio.Queue[bytes] = asyncio.Queue()

class udp_connection(asyncio.DatagramProtocol):
    def __init__(self, addr: tuple[str, int]|None = None) -> None:
        self.key_addr = addr
        self.messages = messages

    def connection_made(self, transport: asyncio.DatagramTransport | asyncio.BaseTransport) -> None:
        self.transport: asyncio.DatagramTransport
        self.transport = transport # type: ignore

    def datagram_received(self, data: bytes, addr: addr_type) -> None:
        key_addr = self.key_addr if self.key_addr is not None else addr
        print('send', data, key_addr)
        data_str = base64.b64encode(data).decode()
        data = json.dumps([data_str, list(key_addr)]).encode()
        data = len(data).to_bytes(8, 'little') + data
        while self.messages.qsize() > 8:
            self.messages.get_nowait()
        self.messages.put_nowait(data)

async def read_data(tcp_connection: stream.Stream) -> tuple[addr_type, bytes]:
    message = await tcp_connection.readexactly(int.from_bytes(await tcp_connection.readexactly(8), 'little'))
    data, addr = json.loads(message)
    addr = tuple(addr)
    data = base64.b64decode(data)
    print('recv', data, addr)
    return addr, data


async def tcp_to_udp(tcp: stream.Stream, udps: typing.Callable[[addr_type], typing.Awaitable[tuple[udp_connection, addr_type]]]) -> None:
    while 1:
        key_addr, data = await read_data(tcp)
        if not key_addr:
            global last_message
            last_message = time.monotonic()
            continue
        udp = await udps(key_addr)
        # if isinstance(udp, collections.abc.Coroutine):
        #     udp = await udp
        udp[0].transport.sendto(data, udp[1])

async def tcp_write(tcp: stream.Stream, data: bytes) -> None:
    tcp.write(data)
    await timeout.run_with_timeout(tcp.drain(), 5)

async def udp_to_tcp(tcp: stream.Stream) -> None:
    while 1:
        data = await messages.get()
        await tcp_write(tcp, data)

def socket(value: str) -> addr_type:
    host, port = re.match(r'(.*):(\d*)', value).groups() # type: ignore
    port = int(port)
    return host, port

def args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument('--tcp', type=socket)
    parser.add_argument('--udp', type=socket)
    return parser.parse_args()

async def connection_loop(reader: asyncio.StreamReader, writer: asyncio.StreamWriter, get_udp:  typing.Callable[[addr_type], typing.Awaitable[tuple[udp_connection, addr_type]]]) -> None:
    async with stream.Stream(reader, writer) as tcp_connection:
        try:
            await asyncio.gather(
                tcp_to_udp(tcp_connection, get_udp),
                udp_to_tcp(tcp_connection),
                send_ping(tcp_connection)
            )
        except Exception as e:
            print(e)

last_message = 0
async def send_ping(tcp: stream.Stream):
    while 1:
        data = json.dumps(['', '']).encode()
        data = len(data).to_bytes(8, 'little') + data
        await tcp_write(tcp, data)
        await asyncio.sleep(30)
        assert time.monotonic() - last_message < 60
