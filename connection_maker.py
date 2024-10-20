import asyncio
import stream
import argparse
import forwarding_parser
import logging
import timeout
import typing

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(levelname)8s %(asctime)s %(filename)s:%(lineno)d %(funcName)s\t\t%(message)s')

args = argparse.Namespace()
unused_connections : asyncio.Queue[tuple[stream.Stream, asyncio.Queue[None], asyncio.Queue[None]]] = asyncio.Queue()
connection_request : asyncio.Queue[None] = asyncio.Queue()

async def copy(rsock: stream.Stream, wsock: stream.Stream):
    while (data := await rsock.safe_read(2**16)):
        await wsock.safe_write(data)
    await wsock.safe_write_eof()

T = typing.TypeVar('T')
def remove_from_queue(q: asyncio.Queue[T], elem: T) -> asyncio.Queue[T]:
    r = asyncio.Queue()
    while not q.empty():
        s = q.get_nowait()
        if s is not elem:
            r.put_nowait(s)
    return r

async def make_connection():
    global unused_connections
    async with stream.Stream(asyncio.open_connection(*args.connect[0])) as client_sock:
        a = (client_sock, asyncio.Queue(), asyncio.Queue())
        unused_connections.put_nowait(a)
        try:
            logger.debug(f'Created unused connection. Waiting for user.')
            await timeout.run_with_timeout(a[1].get(), args.max_unused_connection_time)
            logger.debug(f'Got user.')
        except asyncio.TimeoutError:
            logger.debug(f'No user. Exiting.')
            return
        finally:
            logger.debug(f'Removing self from queue.')
            unused_connections = remove_from_queue(unused_connections, a)
        logger.debug(f'Waiting for connection to end.')
        await a[2].get()
        logger.debug(f'Connection ended.')
        

async def connection_maker_1():
    while 1:
        if unused_connections.qsize() < args.max_unused_connections:
            logger.debug(f'having {unused_connections.qsize()} unused connections, so sending request.')
            connection_request.put_nowait(None)
        else:
            logger.debug(f'having {unused_connections.qsize()} unused connections, so NOT sending request.')
        await asyncio.sleep(args.interval)

async def connection_maker_2():
    while 1:
        await connection_request.get()
        logger.debug(f'got connection request, starting connectoin.')
        asyncio.create_task(make_connection())

@stream.streamify
async def con_handler(server_sock: stream.Stream) -> None:
    if unused_connections.empty():
        logger.debug(f'Got client. no unused connections so sending a request.')
        connection_request.put_nowait(None)
    logger.debug(f'Got client. Waiting for connection to use.')
    client_connection = await unused_connections.get()
    logger.debug(f'Got connection to use for client.')
    client_sock = client_connection[0]
    client_connection[1].put_nowait(None)
    try:
        logger.debug(f'Starting to copy connections.')
        await asyncio.gather(
            copy(server_sock, client_sock),
            copy(client_sock, server_sock),
        )
    finally:
        logger.debug(f'Connection stopped.')
        client_connection[2].put_nowait(None)

async def main():
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('--listen', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--connect', type=forwarding_parser.ColonSeparatedSocketSequence(1), required=True)
    parser.add_argument('--interval', type=float, required=True)
    parser.add_argument('--max-unused-connections', type=int, required=True)
    parser.add_argument('--max-unused-connection-time', type=float, required=True)
    args = parser.parse_args()
    asyncio.create_task(connection_maker_1())
    asyncio.create_task(connection_maker_2())
    async with await asyncio.start_server(con_handler, *args.listen[0]) as server:
        await server.serve_forever()

if __name__ == '__main__':
    asyncio.run(main())
