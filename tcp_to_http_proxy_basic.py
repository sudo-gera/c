#!/usr/bin/env python3

import asyncio
import argparse
import base64
import sys


BUFFER_SIZE = 64 * 1024


async def pipe(reader: asyncio.StreamReader,
               writer: asyncio.StreamWriter):
    """
    Forward bytes from reader to writer.
    Implements proper half-close handling.
    """
    try:
        while True:
            data = await reader.read(BUFFER_SIZE)
            if not data:
                # EOF from source
                try:
                    writer.write_eof()
                except (AttributeError, OSError):
                    pass
                break

            writer.write(data)
            await writer.drain()
    except Exception:
        # On error, attempt half-close
        try:
            writer.write_eof()
        except Exception:
            pass
        raise


async def establish_proxy_tunnel(proxy_host,
                                 proxy_port,
                                 proxy_username,
                                 proxy_password,
                                 target_host,
                                 target_port):
    """
    Establish HTTP CONNECT tunnel through proxy.
    Returns (reader, writer) connected to proxy tunnel.
    Raises on failure.
    """
    reader, writer = await asyncio.open_connection(proxy_host, proxy_port)

    try:
        credentials = f"{proxy_username}:{proxy_password}".encode()
        b64_credentials = base64.b64encode(credentials).decode()

        request = (
            f"CONNECT {target_host}:{target_port} HTTP/1.1\r\n"
            f"Host: {target_host}:{target_port}\r\n"
            f"Proxy-Authorization: Basic {b64_credentials}\r\n"
            f"\r\n"
        )

        writer.write(request.encode("ascii"))
        await writer.drain()

        # Read until end of headers
        response = await reader.readuntil(b"\r\n\r\n")
        header_text = response.decode("iso-8859-1")

        # Parse status line
        status_line = header_text.split("\r\n", 1)[0]
        parts = status_line.split(" ", 2)

        if len(parts) < 2:
            raise RuntimeError("Invalid proxy response")

        status_code = parts[1]

        if status_code != "200":
            raise RuntimeError(f"Proxy CONNECT failed: {status_line}")

        return reader, writer

    except Exception:
        writer.close()
        await writer.wait_closed()
        raise


async def handle_client(client_reader: asyncio.StreamReader,
                        client_writer: asyncio.StreamWriter,
                        args):
    """
    Handle a single incoming client connection.
    Creates one independent proxy tunnel.
    """
    proxy_reader = None
    proxy_writer = None

    try:
        try:
            proxy_reader, proxy_writer = await establish_proxy_tunnel(
                args.proxy_host,
                args.proxy_port,
                args.proxy_username,
                args.proxy_password,
                args.target_host,
                args.target_port,
            )
        except Exception:
            # Proxy connection failed — close client cleanly
            return

        # Forward in both directions independently
        await asyncio.gather(
            pipe(client_reader, proxy_writer),
            pipe(proxy_reader, client_writer),
        )

    finally:
        # Deterministic cleanup
        if proxy_writer is not None:
            try:
                proxy_writer.close()
                await proxy_writer.wait_closed()
            except Exception:
                pass

        try:
            client_writer.close()
            await client_writer.wait_closed()
        except Exception:
            pass


async def main():
    parser = argparse.ArgumentParser(
        description="Asyncio TCP forwarder via HTTP proxy CONNECT"
    )

    parser.add_argument("listen_host")
    parser.add_argument("listen_port", type=int)
    parser.add_argument("proxy_host")
    parser.add_argument("proxy_port", type=int)
    parser.add_argument("proxy_username")
    parser.add_argument("proxy_password")
    parser.add_argument("target_host")
    parser.add_argument("target_port", type=int)

    args = parser.parse_args()

    server = await asyncio.start_server(
        lambda r, w: handle_client(r, w, args),
        args.listen_host,
        args.listen_port,
    )

    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        sys.exit(0)
