<<<<<<< HEAD
for q in range(60):
 for w in range(5):
  a=q*2
  s=q*3
  a-=w
  s-=4-w
  if a*4==s*3:
   print(a+w,s+4-w)

=======
from http.server import BaseHTTPRequestHandler, HTTPServer
import time

hostName = "0.0.0.0"
hostPort = 9000

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html; charset=utf-8")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title>Title goes here.</title></head>".encode()))
        self.wfile.write(bytes("<body><p>This is a test.</p>".encode()))
        self.wfile.write(bytes(("<p>You accessed path: %s</p>" % self.path).encode()))
        self.wfile.write(bytes("</body></html>".encode()))

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))



>>>>>>> 4bbbd537e2b77839d1cb2a08cf6fb785695d288b
