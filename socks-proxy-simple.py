#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 一个简单的 Socks5 代理服务器 , 只有 server 端 , 而且代码比较乱
# 不是很稳定 , 而且使用多线程并不是 select 模型
# Author : WangYihang <wangyihanger@gmail.com>

# modified by sudo-gera

from python_socks.sync import Proxy
proxy = Proxy.from_url('http://127.0.0.1:8899')


import socket
import socket as socket_module
import threading
import sys
from typing import Literal


def handle(buffer: bytes) -> bytes:
    return buffer


def transfer(src: socket_module.socket, dst: socket_module.socket) -> None:
    src_name = src.getsockname()
    src_address = src_name[0]
    src_port = src_name[1]
    dst_name = dst.getsockname()
    dst_address = dst_name[0]
    dst_port = dst_name[1]
    print( "[+] Starting transfer [%s:%d] => [%s:%d]" % (src_name, src_port, dst_name, dst_port))
    while True:
        try:
            buffer = src.recv(0x1000)
        except OSError:
            buffer = b''
        if not buffer:
            print( "[-] No data received! Breaking...")
            break
        # print( "[+] %s:%d => %s:%d [%s]" % (src_address, src_port, dst_address, dst_port, repr(buffer)))
        print( "[+] %s:%d => %s:%d => Length : [%d]" % (src_address, src_port, dst_address, dst_port, len(buffer)))
        dst.send(handle(buffer))
    print( "[+] Closing connecions! [%s:%d]" % (src_address, src_port))
    src.close()
    print( "[+] Closing connecions! [%s:%d]" % (dst_address, dst_port))
    dst.close()


SOCKS_VERSION = 5

ERROR_VERSION = "[-] Client version error!"
ERROR_METHOD = "[-] Client method error!"

# ALLOWED_METHOD = [0, 2]
ALLOWED_METHOD = [0]

def socks_selection(socket: socket_module.socket) -> (
        tuple[Literal[False], str]
            |
        tuple[Literal[True], socket_module.socket]
    ):
    client_version = ord(socket.recv(1))
    print( "[+] client version : %d" % (client_version))
    if not client_version == SOCKS_VERSION:
        socket.shutdown(socket_module.SHUT_RDWR)
        socket.close()
        return (False, ERROR_VERSION)
    support_method_number = ord(socket.recv(1))
    print( "[+] Client Supported method number : %d" % (support_method_number))
    support_methods = []
    for i in range(support_method_number):
        method = ord(socket.recv(1))
        print( "[+] Client Method : %d" % (method))
        support_methods.append(method)
    selected_method = None
    for method in ALLOWED_METHOD:
        if method in support_methods:
            selected_method = 0
    if selected_method is None:
        socket.shutdown(socket_module.SHUT_RDWR)
        socket.close()
        return (False, ERROR_METHOD)
    print( "[+] Server select method : %d" % (selected_method))
    response = chr(SOCKS_VERSION) + chr(selected_method)
    socket.send(response.encode())
    return (True, socket)

CONNECT = 1
BIND = 2
UDP_ASSOCIATE = 3

IPV4 = 1
DOMAINNAME = 3
IPV6 = 4

CONNECT_SUCCESS = 0

ERROR_ATYPE = "[-] Client address error!"

RSV = 0
BNDADDR = "\x00" * 4
BNDPORT = "\x00" * 2

ERROR_RSV = '...unknown...'
ERROR_CMD = '...unknown...'

def socks_request(local_socket: socket_module.socket) -> (
    tuple[Literal[False], str]
    |
    tuple[Literal[True], tuple[socket_module.socket, socket_module.socket]]
    |
    tuple[Literal[True], socket_module.socket]
    ):
    client_version = ord(local_socket.recv(1))
    print( "[+] client version : %d" % (client_version))
    if not client_version == SOCKS_VERSION:
        local_socket.shutdown(socket_module.SHUT_RDWR)
        local_socket.close()
        return (False, ERROR_VERSION)
    cmd = ord(local_socket.recv(1))
    if cmd == CONNECT:
        print( "[+] CONNECT request from client")
        rsv  = ord(local_socket.recv(1))
        if rsv != 0:
            local_socket.shutdown(socket_module.SHUT_RDWR)
            local_socket.close()
            return (False, ERROR_RSV)
        atype = ord(local_socket.recv(1))
        if atype == IPV4:
            dst_address: str|int = ("".join(["%d." % ((i)) for i in local_socket.recv(4)]))[0:-1]
            print( "[+] IPv4 : %s" % (dst_address))
            dst_port = ord(local_socket.recv(1)) * 0x100 + ord(local_socket.recv(1))
            print( "[+] Port : %s" % (dst_port))
            try:
                print( "[+] Connecting : %s:%s" % (dst_address, dst_port))
                # remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                remote_socket = proxy.connect(dst_address, dst_port)
                # remote_socket.connect((dst_address, dst_port))
                response = ""
                response += chr(SOCKS_VERSION)
                response += chr(CONNECT_SUCCESS)
                response += chr(RSV)
                response += chr(IPV4)
                response += BNDADDR
                response += BNDPORT
                local_socket.send(response.encode())
                print( "[+] Tunnel connected! Tranfering data...")
                r = threading.Thread(target=transfer, args=(
                    local_socket, remote_socket))
                r.start()
                s = threading.Thread(target=transfer, args=(
                    remote_socket, local_socket))
                s.start()
                return (True, (local_socket, remote_socket))
            except socket.error as e:
                print( e)
                remote_socket.shutdown(socket.SHUT_RDWR)
                remote_socket.close()
                local_socket.shutdown(socket.SHUT_RDWR)
                local_socket.close()
        elif atype == DOMAINNAME:
            domainname_length = ord(local_socket.recv(1))
            domainname = b""
            for i in range(domainname_length):
                domainname += (local_socket.recv(1))
            print( "[+] Domain name : %r" % (domainname))
            dst_port = ord(local_socket.recv(1)) * 0x100 + ord(local_socket.recv(1))
            print( "[+] Port : %s" % (dst_port))
            try:
                print( "[+] Connecting : %r:%r" % (domainname, dst_port))
                # remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                # remote_socket.connect((domainname, dst_port))
                remote_socket = proxy.connect(domainname.decode(), dst_port)
                response = ""
                response += chr(SOCKS_VERSION)
                response += chr(CONNECT_SUCCESS)
                response += chr(RSV)
                response += chr(IPV4)
                response += BNDADDR
                response += BNDPORT
                local_socket.send(response.encode())
                print( "[+] Tunnel connected! Tranfering data...")
                r = threading.Thread(target=transfer, args=(
                    local_socket, remote_socket))
                r.start()
                s = threading.Thread(target=transfer, args=(
                    remote_socket, local_socket))
                s.start()
                return (True, (local_socket, remote_socket))
            except socket.error as e:
                print( e)
                remote_socket.shutdown(socket.SHUT_RDWR)
                remote_socket.close()
                local_socket.shutdown(socket.SHUT_RDWR)
                local_socket.close()
        elif atype == IPV6:
            dst_address = int.from_bytes(local_socket.recv(4), 'big')
            print( "[+] IPv6 : %x" % (dst_address))
            dst_port = ord(local_socket.recv(1)) * 0x100 + ord(local_socket.recv(1))
            print( "[+] Port : %s" % (dst_port))
            # remote_socket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
            # remote_socket.connect((dst_address, dst_port))
            remote_socket = proxy.connect(dst_address, dst_port)
            local_socket.shutdown(socket.SHUT_RDWR)
            local_socket.close()
            return (False, ERROR_ATYPE)
        else:
            local_socket.shutdown(socket.SHUT_RDWR)
            local_socket.close()
            return (False, ERROR_ATYPE)
    elif cmd == BIND:
        # TODO
        local_socket.shutdown(socket.SHUT_RDWR)
        local_socket.close()
        return (False, ERROR_CMD)
    elif cmd == UDP_ASSOCIATE:
        # TODO
        local_socket.shutdown(socket.SHUT_RDWR)
        local_socket.close()
        return (False, ERROR_CMD)
    else:
        local_socket.shutdown(socket.SHUT_RDWR)
        local_socket.close()
        return (False, ERROR_CMD)
    return (True, local_socket)

def server(local_host: str, local_port: int, max_connection: int) -> None:
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((local_host, local_port))
        server_socket.listen(max_connection)
        print( '[+] Server started [%s:%d]' % (local_host, local_port))
        while True:
            local_socket, local_address = server_socket.accept()
            print( '[+] Detect connection from [%s:%s]' % (local_address[0], local_address[1]))
            result = socks_selection(local_socket)
            if not result[0]:
                print( "[-] socks selection error!")
                break
            result_ = socks_request(result[1])
            if not result_[0]:
                print( "[-] socks request error!")
                break
            # local_socket, remote_socket = result[1]
            # TODO : loop all socket to close...
        print( "[+] Releasing resources...")
        local_socket.close()
        print( "[+] Closing server...")
        server_socket.close()
        print( "[+] Server shuted down!")
    except  KeyboardInterrupt:
        print( ' Ctl-C stop server')
        # try:
        #     remote_socket.close()
        # except:
        #     pass
        try:
            local_socket.close()
        except:
            pass
        try:
            server_socket.close()
        except:
            pass
        return


def main() -> None:
    if len(sys.argv) != 3:
        print( "Usage : ")
        print( "\tpython %s [L_HOST] [L_PORT]" % (sys.argv[0]))
        print( "Example : ")
        print( "\tpython %s 127.0.0.1 1080" % (sys.argv[0]))
        print( "Author : ")
        print( "\tWangYihang <wangyihanger@gmail.com>")
        exit(1)
    LOCAL_HOST = sys.argv[1]
    LOCAL_PORT = int(sys.argv[2])
    #REMOTE_HOST = sys.argv[3]
    #REMOTE_PORT = int(sys.argv[4])
    MAX_CONNECTION = 0x10
    server(LOCAL_HOST, LOCAL_PORT, MAX_CONNECTION)


if __name__ == "__main__":
    main()
