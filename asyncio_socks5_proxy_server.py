import asyncio
import argparse
import ipaddress

args: argparse.Namespace

def pretty_bytes(data: bytes) -> str:
    return '\n'.join(map(repr, data.split(b'\n')))

async def copy(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    while (data := await reader.read(2**16)):
        # print('got data:', pretty_bytes(data))
        writer.write(data)
        await writer.drain()
    writer.write_eof()

async def handle_accepted_connection(a_reader: asyncio.StreamReader, a_writer: asyncio.StreamWriter) -> None:
    try:
        print('accceted new connection')
        socks_ver = await a_reader.readexactly(1)
        assert socks_ver == b'\x05'

        methods_len = int.from_bytes(await a_reader.readexactly(1), 'big')
        methods = await a_reader.readexactly(methods_len)

        assert b'\x00' in methods

        print(f'client auth methods: {methods}')

        a_writer.write(b'\x05\x00')
        await a_writer.drain()

        socks_ver = await a_reader.readexactly(1)
        assert socks_ver == b'\x05'

        cmd = await a_reader.readexactly(1)
        assert cmd == b'\x01'

        rsv = await a_reader.readexactly(1)
        assert rsv == b'\x00'

        atyp = await a_reader.readexactly(1)
        assert atyp in b'\x01\x03\x04'

        if atyp == b'\x01':
            print(f'addr type: ipv4')
            addr_b = await a_reader.readexactly(4)
            addr = str(ipaddress.IPv4Address(addr_b))
        if atyp == b'\x04':
            print(f'addr type: ipv6')
            addr_b = await a_reader.readexactly(16)
            addr = str(ipaddress.IPv6Address(addr_b))
        if atyp == b'\x03':
            print(f'addr type: domain')
            addr_len = int.from_bytes(await a_reader.readexactly(1), 'big')
            addr = (await a_reader.readexactly(addr_len)).decode()

        port = int.from_bytes(await a_reader.readexactly(2), 'big')

        print(f'request to {addr}:{port}')

        c_reader, c_writer = await asyncio.open_connection(addr, port)
        try:
            print(f'connected to {addr}:{port}')

            a_writer.write(b'\x05\x00\x00'b'\x01'b'\x7f\x00\x00\x01'b'\x00\x00')
            await a_writer.drain()

            await asyncio.gather(
                copy(a_reader, c_writer),
                copy(c_reader, a_writer),
            )
        finally:
            c_writer.close()
            await c_writer.wait_closed()
            print('closing connected connection')
    finally:
        a_writer.close()
        await a_writer.wait_closed()
        print('closing accepted connection')

async def main(args: argparse.Namespace) -> None:
    server = await asyncio.start_server(handle_accepted_connection, args.listen_host, args.listen_port)
    async with server:
        await server.serve_forever()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen-host', type=str, required=True)
    parser.add_argument('--listen-port', type=int, required=True)
    # parser.add_argument('--connect-host', type=str, required=True)
    # parser.add_argument('--connect-port', type=int, required=True)
    args=parser.parse_args()
    asyncio.run(main(args))


