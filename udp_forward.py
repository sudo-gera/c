import asyncio
import argparse

import forwarding_parser

args = argparse.Namespace()

class Connection:
    ...


async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    global args
    args = parser.parse_args()

    server, _ = await asyncio.get_running_loop().create_datagram_endpoint(
        Connection,
        *args.listen[0],
    )

    try:
        await asyncio.Future()
    finally:
        server.close()

if __name__ == '__main__':
    asyncio.run(main)