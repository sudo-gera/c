import asyncio
import ssl

from aioquic.asyncio.client import connect
from aioquic.h3.connection import H3_ALPN
from aioquic.quic.configuration import QuicConfiguration


async def main():
    cfg = QuicConfiguration(
        is_client=True,
        alpn_protocols=H3_ALPN,
        verify_mode=ssl.CERT_REQUIRED,
        server_name="ozon.ru",
    )

    try:
        async with connect(
            "ozon.ru",
            443,
            configuration=cfg,
        ):
            print("QUIC handshake: OK")
            print("TLS 1.3 handshake: OK")
            print("ALPN: h3")

    except Exception as e:
        print("Handshake failed:", e)


asyncio.run(main())
