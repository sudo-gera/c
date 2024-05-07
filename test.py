from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import traceback

hostName = "0.0.0.0"
hostPort = 9000

class MyServer(BaseHTTPRequestHandler):
    def setup(self) -> None:
        res = super().setup()
        self.rfile.readline___ = self.rfile.readline
        self.rfile.readline = lambda *a, **s: [[print(q),q][-1] for q in [print(a,s), traceback.print_stack(), self.rfile.readline___(*a, **s)][-1:]][0]
        return res
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title>Title goes here.</title></head>".encode()))
        self.wfile.write(bytes("<body><p>This is a test.</p>".encode()))
        self.wfile.write(bytes(("<p>You accessed path: %s</p>" % self.path).encode()))
        self.wfile.write(bytes("</body></html>".encode()))
    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        # lenn=int(self.headers['Content-Length'])
        # data=self.rfile.read(lenn)
        self.wfile.write(bytes("<html><head><title>Title goes here.</title></head>".encode()))
        self.wfile.write(bytes("<body><p>This is a test.</p>".encode()))
        self.wfile.write(bytes(("<p>You accessed path: %s</p>" % self.path).encode()))
        # self.wfile.write(bytes(("<p>data: %s</p>" % repr(data)).encode()))
        self.wfile.write(bytes("</body></html>".encode()))
        # self.wfile.write(bytes(data))

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))
