import asyncio
import argparse
import pickle

import forwarding
import stream

# def create_server():

def parse_args():
    parser=argparse.ArgumentParser()
    parser.add_argument('--listen', action='store_true')
    # parser.add_argument('-L', type=forwarding.forwarding(2), action='append')
    # parser.add_argument('-R', type=forwarding.forwarding(2), action='append')
    parser.add_argument('addr', type=forwarding.forwarding(1))
    args = parser.parse_args()
    return args

async def server_connection(reader, writer):
    async with stream.Stream(reader, writer) as sock:
        while 1:
            message = await sock.readexactly(int.from_bytes(await sock.readexactly(8), 'little'))
            sock.write(len(message).to_bytes(8, 'little'))
            sock.write(message)
            await sock.drain()

async def client_connection(reader, writer):
    async with stream.Stream(reader, writer) as sock:
        message = None
        while 1:
            message = yield message
            message = pickle.dumps(message)
            sock.write(len(message).to_bytes(8, 'little'))
            sock.write(message)
            await sock.drain()
            message = await sock.readexactly(int.from_bytes(await sock.readexactly(8), 'little'))
            message = pickle.loads(message)

async def start_forwarding(message):
    print(repr(message))

async def main():
    args = parse_args()
    if args.listen:
        server = await asyncio.start_server(server_connection, *args.addr[0].values())
        conn = client_connection(*await asyncio.open_connection('127.0.0.1', args.addr[0].port))
        await conn.asend(None)
    else:
        conn = client_connection(*await asyncio.open_connection(*args.addr[0].values()))
        await conn.asend(None)
    print(await conn.asend(1))
    print(await conn.asend(2))
    print(await conn.asend(3))

    # for f in [] if args.L is None else args.L:
    #     print(f)
    # for f in [] if args.R is None else args.R:
    #     print(f)
    

asyncio.run(main())




# import asyncio
# from typing import Any
# import secrets
# import json
# import functools

# import stream
# import forwarding


# def handle_user_message(message):
    









# # import asyncio
# # from typing import Any
# # import secrets
# # import json
# # import functools

# # import stream
# # import forwarding

# # events = asyncio.Queue()

# # address_mappping = {}


# # class udp_connection(asyncio.DatagramProtocol):
# #     def __init__(self, client_addr = None):
# #         self.client_addr = client_addr

# #     def connection_made(self, transport: asyncio.DatagramTransport) -> None:
# #         self.transport = transport

# #     def datagram_received(self, data: bytes, addr: tuple[str | Any, int]) -> None:
# #         if self.client_addr is not None:
# #             self.server_addr = addr
# #             addr = self.client_addr
# #         message = json.dumps(addr).encode() + '\0' + data
# #         size = len(message)
# #         sock.write(size.to_bytes(8, 'little'))
# #         sock.write(message)
    
# # connection_by_addr : dict[Any, udp_connection] = {}
# # # async def main():

# # async def start_forwarding(server_addr):
    

# # async def tcp_recv(reader, writer):
# #     global sock
# #     async with stream.Stream(reader, writer) as sock:
# #         while 1:
# #             size = int.from_bytes(await sock.readexactly(8), 'little')
# #             message = await sock.readexactly(size)
# #             message, data = message.split('\0', 1) if '\0' in message else message, b''
# #             message = json.loads(message)
            

# #             addr = json.loads(addr.decode())
# #             if addr not in connection_by_addr:
# #                 loop = asyncio.get_event_loop()
# #                 connection_by_addr[addr] = await loop.create_datagram_endpoint(
# #                     functools.partial(udp_connection, addr),
# #                     remote_addr=addr,
# #                 )
# #             connection_by_addr[addr].transport.sendto(data)

# # def address(addr):
# #     return forwarding.forwarding('127.0.0.1:9999:'+addr)[1]

# # async def main():
# #     parser = argparse.ArgumentParser()
# #     parser.add_argument('-L', action='append', type=forwarding.forwarding)
# #     parser.add_argument('-R', action='append', type=forwarding.forwarding)
# #     parser.add_argument('-l', nargs='?', type='store_true')
# #     parser.add_argument('address', type=address)
# #     args = parser.parse_args()
# #     if args.l:
# #         async with await asyncio.start_server(tcp_recv, *args.address) as server:
# #             await server.serve_forever()
# #     else:
# #         sock = await asyncio.open_connection(*args.address)
# #         for arg in args.L:
# #             await start_forwarding(arg)
# #         for arg in args.R:
            

# if __name__ == '__main__':
#     asyncio.run(main())



# import sys
# import socket
# import argparse
# import queue
# import asyncio
# import threading

# def get_args():
#     parser = argparse.ArgumentParser(description='each option requires host:port format')
#     parser.add_argument('--udp-listen')
#     parser.add_argument('--udp-connect')
#     parser.add_argument('--tcp-listen')
#     parser.add_argument('--tcp-connect')
#     return parser.parse_args()

# args=get_args()
# def split(s):
#     h,p=(':'+s).split(':')[-2:]
#     p=int(p)
#     return h,p

# if [args.tcp_listen,args.tcp_connect].count(None)!=1:
#     print('error')
#     exit(1)

# if [args.udp_listen,args.udp_connect].count(None)!=1:
#     print('error')
#     exit(1)

# udp_s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# if args.udp_listen:
#     udp_s.bind(split(args.udp_listen))

# # if args.tcp_listen:
# #     tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# #     tcp_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# #     tcp_s.bind(split(args.tcp_listen))
# #     tcp_s.listen(200)
# # else:
# #     tcp_s.connect(split(args.tcp_connect))

# udp_host=split(args.udp_connect) if args.udp_connect else None

# def tcp_server():
#     if args.tcp_listen:
#         tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         tcp_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#         tcp_s.bind(split(args.tcp_listen))
#         tcp_s.listen(200)
#         while 1:
#             tcp_client,addr=tcp_s.accept()
#             threading.Thread(target=t2u, args=(tcp_client,)).start()
#             threading.Thread(target=u2t, args=(tcp_client,)).start()
#     else:
#         tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         tcp_s.connect(split(args.tcp_connect))
#         threading.Thread(target=t2u, args=(tcp_s,)).start()
#         threading.Thread(target=u2t, args=(tcp_s,)).start()

# def t2u(tcp_client):
#     data=tcp_client.recv(65536)
#     while data:
#         print(len(data))
#         udp_s.sendto(data,udp_host)
#         data=tcp_client.recv(65536)


# def u2t(tcp_client):
#     global udp_host
#     data,udp_host=udp_s.recvfrom(65536)
#     while data:
#         print(len(data))
#         tcp_client.send(data)
#         data,udp_host=udp_s.recvfrom(65536)

# tcp_server()
