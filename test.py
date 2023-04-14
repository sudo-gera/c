import http.server
import socket
import select
import time
import sys
import os
import base64
import json
from icecream import ic

# class Server:

#     def create_server(self, host, port):
#         server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#         server.bind((host, port))
#         server.listen(200)
#         self.input[server]={
#             'on_event': self.on_accept,
#         }

#     def __init__(self):
#         self.input={}
#         self.client_by_id={}

#     def main_loop(self):
#         ss = select.select
#         while 1:
#             input_ready, output_ready, except_ready = ss(self.input.keys(), [], [])
#             ic('got event')
#             for s in input_ready:
#                 if not self.input[s]['on_event'](s):
#                     break

#     def on_event(self,client):
#         try:
#             data = client.recv(65536)
#         except ConnectionResetError:
#             data = ''
#         if not data:
#             self.on_close(client)
#         else:
#             self.on_recv(client,data)
#             return 1

#     def on_accept(self,server):
#         client, client_addr = server.accept()
#         print (client_addr, "has connected")
#         client_id = int(time.time()*2**128)
#         self.client_by_id[client_id]=client
#         self.input[client]={
#             'on_event': self.on_event,
#             'id': client_id,
#         }

#     def on_close(self,client):
#         try:
#             n=client.getpeername()
#         except OSError:
#             n='(undefined)'
#         print (n, "has disconnected")
#         client_id=self.input[client]['id']
#         client.close()
#         del self.input[client]
#         del self.client_by_id[client_id]

#     def on_recv(self,client,data):
#         client_id=self.input[client]['id']
#         ic(client_id,data)
#         meth

#     def __del__(self):
#         for w in self.input:
#             w.close()

# s=Server()
# s.create_server('',9009)
# s.main_loop()

from http.server import BaseHTTPRequestHandler, HTTPServer
import time

hostName = "0.0.0.0"
hostPort = 9009

class MyServer(BaseHTTPRequestHandler):
    def parse_request(self) -> bool:
        ic(self.raw_requestline)
        return super().parse_request()

    def do_GET(self):
        ic(list(self.headers.items()))
        if self.headers['Connection']=='Upgrade' and self.headers['Upgrade']=='websocket':
            self.send_response(101)
            self.send_header("Upgrade", "websocket")
            self.send_header("Connection", "Upgrade")
            return
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        # self.wfile.write(bytes("<html><head><title>Title goes here.</title></head>".encode()))
        # self.wfile.write(bytes("<body><p>This is a test.</p>".encode()))
        # self.wfile.write(bytes(("<p>You accessed path: %s</p>" % self.path).encode()))
        # self.wfile.write(bytes("</body></html>".encode()))

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))








