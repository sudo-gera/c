import ipaddress
import sys
import psutil
import asyncio
from urllib.parse import quote, unquote

async def safe_socket_close(writer: asyncio.StreamWriter) -> None:
    try:
        writer.write_eof()
    except Exception:
        pass
    try:
        await run_with_timeout(writer.drain(), 1)
    except Exception:
        pass
    try:
        writer.close()
    except Exception:
        pass
    try:
        await run_with_timeout(writer.wait_closed(), 1)
    except Exception:
        pass

# def get_network(network_mask: str) -> list[str]:
#     return [*map(str, ipaddress.ip_network(network_mask).hosts())]

# def get_my_ip(network_mask: str) -> str:
#     network = get_network(network_mask)
#     ifaces = psutil.net_if_addrs()
#     for addresses_of_iface in ifaces.values():
#         for address_info in addresses_of_iface:
#             addr = address_info.address
#             if addr in network:
#                 return addr
#     print(network, file=sys.stderr)
#     print(ifaces, file=sys.stderr)
#     assert False

def select_my_ip(ips: list[str]) -> str:
    ifaces = psutil.net_if_addrs()
    for addresses_of_iface in ifaces.values():
        for address_info in addresses_of_iface:
            addr = address_info.address
            if addr in ips:
                return addr
    print(ips, file=sys.stderr)
    print(ifaces, file=sys.stderr)
    assert False

import asyncio
import traceback
import typing

T = typing.TypeVar('T')

async def run_with_timeout(coro: typing.Coroutine[typing.Any, typing.Any, T], timeout: float) -> T:
    task = asyncio.create_task(coro)
    e = None
    try:
        await asyncio.wait([task], timeout=timeout)
    except BaseException as _e:
        e=_e
    finally:
        if task.done():
            if e is not None:
                raise e
            return task.result()
        task.cancel()
    if e is not None:
        raise e
    raise asyncio.TimeoutError







# str_or_bytes = str | bytes | bytearray

# def str_or_bytes_to_bytes(value: str_or_bytes):
#     if isinstance(value, str):
#         value = value.encode()
#     assert not isinstance(value, str)
#     return value

# def create_http_request(host: str|bytes|bytearray, method:str|bytes|bytearray, path: str|bytes|bytearray, body:str|bytes|bytearray) -> bytes:
#     if isinstance(method, str):
#         method = method.encode()
#     assert not isinstance(method, str)

#     if isinstance(path, str):
#         path = path.encode()
#     assert not isinstance(path, str)

#     if isinstance(body, str):
#         body = body.encode()
#     assert not isinstance(body, str)

#     if isinstance(host, str):
#         host = host.encode()
#     assert not isinstance(host, str)

#     headers = []
#     headers.append(['Host', host])
#     headers.append(['User-Agent', 'potato'])
#     assert method and method.isascii() and all([not chr(c).isspace() for c in method])
#     assert path and all([not chr(c).isspace() for c in path])
#     path = quote(path).encode()
#     if body:
#         headers.append(['Content-Length', str(len(body))])
#     return \
#         method + b' ' + path + ' HTTP/1.1\r\n' \
#         + b'\r\n'.join([b': '.join(header) for header in headers])\
#         + b'\r\n\r\n' + body

# async def http_request(reader: asyncio.StreamReader, writer: asyncio.StreamWriter, host: str, port: int, ):
    


# def parse_http_request(
#     lines = data.splitlines()
#     method, path, *_ = lines[0].split()
