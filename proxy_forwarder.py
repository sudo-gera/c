import asyncio
import base64
import ssl
import sys
from urllib.parse import urlparse


async def tunnel_connection(
    client_reader: asyncio.StreamReader,
    client_writer: asyncio.StreamWriter,
    proxy_host: str,
    proxy_port: int,
    proxy_user: str,
    proxy_pass: str,
    target_host: str,
    target_port: int,
):
    proxy_reader = None
    proxy_writer = None

    try:
        # Connect to HTTPS proxy (TLS to proxy itself)
        ssl_ctx = ssl.create_default_context()
        proxy_reader, proxy_writer = await asyncio.open_connection(
            proxy_host, proxy_port, ssl=ssl_ctx, server_hostname=proxy_host
        )

        # Prepare Proxy-Authorization header
        credentials = f"{proxy_user}:{proxy_pass}".encode()
        auth = base64.b64encode(credentials).decode()

        connect_req = (
            f"CONNECT {target_host}:{target_port} HTTP/1.1\r\n"
            f"Host: {target_host}:{target_port}\r\n"
            f"Proxy-Authorization: Basic {auth}\r\n"
            f"Proxy-Connection: Keep-Alive\r\n"
            f"\r\n"
        )

        proxy_writer.write(connect_req.encode())
        await proxy_writer.drain()

        # Read CONNECT response
        response = await proxy_reader.readuntil(b"\r\n\r\n")
        if b"200" not in response.split(b"\r\n", 1)[0]:
            raise RuntimeError(f"Proxy CONNECT failed:\n{response.decode()}")

        async def pipe(reader, writer):
            try:
                while True:
                    data = await reader.read(65536)
                    if not data:
                        break
                    writer.write(data)
                    await writer.drain()
            except asyncio.CancelledError:
                raise
            except Exception:
                pass
            finally:
                try:
                    writer.write_eof()
                except Exception:
                    pass

        # Bidirectional piping
        task1 = asyncio.create_task(pipe(client_reader, proxy_writer))
        task2 = asyncio.create_task(pipe(proxy_reader, client_writer))

        done, pending = await asyncio.wait(
            [task1, task2],
            return_when=asyncio.FIRST_COMPLETED,
        )

        for t in pending:
            t.cancel()

        await asyncio.gather(*pending, return_exceptions=True)

    except Exception as e:
        print(f"Connection error: {e}", file=sys.stderr)

    finally:
        if proxy_writer:
            proxy_writer.close()
            await proxy_writer.wait_closed()
        client_writer.close()
        await client_writer.wait_closed()


async def start_forwarder(
    listen_host,
    listen_port,
    proxy_host,
    proxy_port,
    proxy_user,
    proxy_pass,
    target_url,
):
    parsed = urlparse(target_url)
    if parsed.scheme != "https":
        raise ValueError("Only https:// URLs are supported")

    target_host = parsed.hostname
    target_port = parsed.port or 443

    async def handler(reader, writer):
        await tunnel_connection(
            reader,
            writer,
            proxy_host,
            proxy_port,
            proxy_user,
            proxy_pass,
            target_host,
            target_port,
        )

    server = await asyncio.start_server(handler, listen_host, listen_port)

    addr = server.sockets[0].getsockname()
    print(f"Listening on {addr}")

    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    if len(sys.argv) != 8:
        print(
            "Usage:\n"
            "python proxy_forwarder.py "
            "<listen_host> <listen_port> "
            "<proxy_host> <proxy_port> "
            "<proxy_user> <proxy_pass> "
            "<target_https_url>"
        )
        sys.exit(1)

    asyncio.run(
        start_forwarder(
            sys.argv[1],
            int(sys.argv[2]),
            sys.argv[3],
            int(sys.argv[4]),
            sys.argv[5],
            sys.argv[6],
            sys.argv[7],
        )
    )
