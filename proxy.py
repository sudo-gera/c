from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.request import urlopen
from shutil import copyfileobj

class file_slice:
    def __init__(self,f,n) -> None:
        self.f=f
        self.n=n
    def read(self,l):
        r=min(l,self.n)
        self.n-=r
        return self.f.read(r)


class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        copyfileobj(urlopen(self.path), self.wfile)
    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        data_len=int(self.headers['Content-Length'])
        copyfileobj(urlopen(self.path, data=file_slice(self.rfile,data_len)), self.wfile)
    # def do_CONNECT(self):
    #     self.send_response(301)
    #     self.send_header("Location", "http://127.0.0.1:1234")
    #     self.end_headers()
        


myServer = HTTPServer(('0.0.0.0', 1234), MyServer)

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    print()

myServer.server_close()
