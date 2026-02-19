import asyncio
import ssl
import argparse


async def pipe(reader: asyncio.StreamReader,
               writer: asyncio.StreamWriter):
    try:
        while True:
            data = await reader.read(65536)

            if not data:
                # Half-close (FIN)
                try:
                    writer.write_eof()
                    await writer.drain()
                except (AttributeError, OSError):
                    pass
                break

            writer.write(data)
            await writer.drain()

    except asyncio.CancelledError:
        raise
    except Exception:
        pass


async def handle_client(local_reader: asyncio.StreamReader,
                        local_writer: asyncio.StreamWriter,
                        target_host: str,
                        target_port: int):

    # Ensure local_writer is always closed
    try:
        ssl_ctx = ssl.create_default_context()
        ssl_ctx.check_hostname = False
        ssl_ctx.verify_mode = ssl.CERT_NONE

        try:
            remote_reader, remote_writer = await asyncio.open_connection(
                target_host,
                target_port,
                ssl=ssl_ctx,
                server_hostname=target_host,
            )
        except Exception:
            return

        # Ensure remote_writer is always closed
        try:
            task_local_to_remote = asyncio.create_task(
                pipe(local_reader, remote_writer)
            )
            task_remote_to_local = asyncio.create_task(
                pipe(remote_reader, local_writer)
            )

            await asyncio.gather(
                task_local_to_remote,
                task_remote_to_local,
                return_exceptions=True,
            )

        finally:
            try:
                remote_writer.close()
            except Exception:
                pass
            try:
                await remote_writer.wait_closed()
            except Exception:
                pass

    finally:
        try:
            local_writer.close()
        except Exception:
            pass
        try:
            await local_writer.wait_closed()
        except Exception:
            pass


async def main():
    parser = argparse.ArgumentParser(
        description="Async TCP to TLS forwarder (no cert verification)"
    )
    parser.add_argument("listen_host")
    parser.add_argument("listen_port", type=int)
    parser.add_argument("target_host")
    parser.add_argument("target_port", type=int)

    args = parser.parse_args()

    server = await asyncio.start_server(
        lambda r, w: handle_client(
            r, w,
            args.target_host,
            args.target_port
        ),
        args.listen_host,
        args.listen_port,
    )

    addrs = ", ".join(str(sock.getsockname()) for sock in server.sockets)
    print(f"Listening on {addrs} → TLS {args.target_host}:{args.target_port}")

    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
