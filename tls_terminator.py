import asyncio
import ssl
import os
import argparse
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.backends import default_backend
from datetime import datetime, timedelta

CERT_FILE = "cert.pem"
KEY_FILE = "key.pem"


def generate_self_signed_cert(cert_file, key_file):
    key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )
    subject = x509.Name([
        x509.NameAttribute(NameOID.COMMON_NAME, u'localhost'),
    ])
    cert = (
        x509.CertificateBuilder()
        .subject_name(subject)
        .issuer_name(subject)
        .public_key(key.public_key())
        .serial_number(x509.random_serial_number())
        .not_valid_before(datetime.utcnow() - timedelta(days=1))
        .not_valid_after(datetime.utcnow() + timedelta(days=365))
        .add_extension(
            x509.SubjectAlternativeName([x509.DNSName(u'localhost')]),
            critical=False
        )
        .sign(key, hashes.SHA256(), backend=default_backend())
    )

    with open(cert_file, "wb") as f:
        f.write(cert.public_bytes(serialization.Encoding.PEM))
    with open(key_file, "wb") as f:
        f.write(key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.TraditionalOpenSSL,
            encryption_algorithm=serialization.NoEncryption()
        ))


def ensure_cert():
    if not os.path.exists(CERT_FILE) or not os.path.exists(KEY_FILE):
        print("Generating self-signed certificate...")
        generate_self_signed_cert(CERT_FILE, KEY_FILE)


async def forward(reader_from, writer_to):
    try:
        while True:
            data = await reader_from.read(4096)
            if not data:
                break
            writer_to.write(data)
            await writer_to.drain()
    except asyncio.CancelledError:
        pass
    finally:
        writer_to.close()
        await writer_to.wait_closed()


async def handle_tls_connection(reader, writer, connect_host, connect_port):
    peername = writer.get_extra_info('peername')
    print(f"[+] Incoming TLS connection from {peername}")

    try:
        remote_reader, remote_writer = await asyncio.open_connection(connect_host, connect_port)
        print(f"[+] Forwarding unencrypted traffic to {connect_host}:{connect_port}")

        task1 = asyncio.create_task(forward(reader, remote_writer))
        task2 = asyncio.create_task(forward(remote_reader, writer))
        await asyncio.gather(task1, task2)
    except Exception as e:
        print(f"[!] Error: {e}")
    finally:
        writer.close()
        await writer.wait_closed()


async def main():
    parser = argparse.ArgumentParser(description="TLS terminator using asyncio")
    parser.add_argument('--listen-host', default='0.0.0.0', help='TLS listen host (default: 0.0.0.0)')
    parser.add_argument('--listen-port', type=int, default=8443, help='TLS listen port (default: 8443)')
    parser.add_argument('--connect-host', default='127.0.0.1', help='Forward target host (default: 127.0.0.1)')
    parser.add_argument('--connect-port', type=int, default=8080, help='Forward target port (default: 8080)')
    args = parser.parse_args()

    ensure_cert()

    ssl_ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ssl_ctx.load_cert_chain(CERT_FILE, KEY_FILE)
    ssl_ctx.set_servername_callback(lambda *args: None)

    server = await asyncio.start_server(
        lambda r, w: handle_tls_connection(r, w, args.connect_host, args.connect_port),
        host=args.listen_host,
        port=args.listen_port,
        ssl=ssl_ctx
    )

    addr = server.sockets[0].getsockname()
    print(f"[*] TLS terminator listening on {addr}")

    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    asyncio.run(main())
