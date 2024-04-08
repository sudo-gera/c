from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import json
import base64
import pickle
import os
import subprocess
import re

hostName = "0.0.0.0"
hostPort = 9000

from collections import deque
q = deque()

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/json; charset=utf-8")
        self.send_header('Access-Control-Allow-Origin', '*')
        self.end_headers()
        path = self.path[1:]
        if path == 'favicon.ico':
            return
        if path:
            for path in json.loads(base64.b64decode(path)):
                q.append(path)
        else:
            while 1:
                try:
                    with open('./../loader/db.json', 'rb') as file:
                        data = file.read()
                    print(len(data))
                    db = pickle.loads(data)
                    break
                except (pickle.UnpicklingError, EOFError):
                    time.sleep(0.1)
            while q:
                path = q.popleft()
                if (match := re.match(r'https://([^/]+):(\d+)(/.*)', path)):
                    path = ' '.join(match.groups())
                elif (match := re.match(r'https://([^/]+)(/.*)', path)):
                    path = ' 443 '.join(match.groups())
                elif (match := re.match(r'http://([^/]+):(\d+)(/.*)', path)):
                    path = ' '.join(match.groups())
                elif (match := re.match(r'http://([^/]+)(/.*)', path)):
                    path = ' 80 '.join(match.groups())
                if path not in db and not path.startswith('mailto://') and not re.findall(r'\bzoom.us\b', path):
                    self.wfile.write(path.encode())
                    break

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))
