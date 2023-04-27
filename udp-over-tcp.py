import sys
import socket
import argparse
import queue
import asyncio
import threading

def get_args():
    parser = argparse.ArgumentParser(description='each option requires host:port format')
    parser.add_argument('--udp-listen')
    parser.add_argument('--udp-connect')
    parser.add_argument('--tcp-listen')
    parser.add_argument('--tcp-connect')
    return parser.parse_args()

args=get_args()
def split(s):
    h,p=(':'+s).split(':')[-2:]
    p=int(p)
    return h,p

if [args.tcp_listen,args.tcp_connect].count(None)!=1:
    print('error')
    exit(1)

if [args.udp_listen,args.udp_connect].count(None)!=1:
    print('error')
    exit(1)

udp_s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
if args.udp_listen:
    udp_s.bind(split(args.udp_listen))

# if args.tcp_listen:
#     tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     tcp_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#     tcp_s.bind(split(args.tcp_listen))
#     tcp_s.listen(200)
# else:
#     tcp_s.connect(split(args.tcp_connect))

udp_host=split(args.udp_connect) if args.udp_connect else None

def tcp_server():
    if args.tcp_listen:
        tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        tcp_s.bind(split(args.tcp_listen))
        tcp_s.listen(200)
        while 1:
            tcp_client,addr=tcp_s.accept()
            threading.Thread(target=t2u, args=(tcp_client,)).start()
            threading.Thread(target=u2t, args=(tcp_client,)).start()
    else:
        tcp_s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp_s.connect(split(args.tcp_connect))
        threading.Thread(target=t2u, args=(tcp_s,)).start()
        threading.Thread(target=u2t, args=(tcp_s,)).start()

def t2u(tcp_client):
    data=tcp_client.recv(65536)
    while data:
        print(len(data))
        udp_s.sendto(data,udp_host)
        data=tcp_client.recv(65536)


def u2t(tcp_client):
    global udp_host
    data,udp_host=udp_s.recvfrom(65536)
    while data:
        print(len(data))
        tcp_client.send(data)
        data,udp_host=udp_s.recvfrom(65536)

tcp_server()
