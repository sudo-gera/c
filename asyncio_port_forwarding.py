import asyncio
import argparse

args: argparse.Namespace

def pretty_bytes(data: bytes) -> str:
    return '\n'.join(map(repr, data.split(b'\n')))

async def copy(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> None:
    while (data := await reader.read(2**16)):
        print('got data:', pretty_bytes(data))
        writer.write(data)
        await writer.drain()
    writer.write_eof()

async def handle_accepted_connection(a_reader: asyncio.StreamReader, a_writer: asyncio.StreamWriter) -> None:
    try:
        print('accceted new connection')
        c_reader, c_writer = await asyncio.open_connection(args.connect_host, args.connect_port)
        try:
            print('connected to destination')
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
    parser.add_argument('--connect-host', type=str, required=True)
    parser.add_argument('--connect-port', type=int, required=True)
    args=parser.parse_args()
    asyncio.run(main(args))


