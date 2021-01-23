from http.server import BaseHTTPRequestHandler, HTTPServer
import time
from urllib.request import urlopen as u

hostName = '127.0.0.1'
hostPort = 9999

class MyServer(BaseHTTPRequestHandler):
	def do_GET(self):
		path=self.path
		####
		self.send_response(200)
		self.send_header("Content-type", "text/html; charset=utf-8")
		self.end_headers()
		self.wfile.write('hello'.encode())

	def do_POST(self):
		lenn=int(self.headers['Content-Length'])
		data=self.rfile.read(lenn)
		path=self.path
		####
		self.send_response(200)
		self.send_header("Content-type", "text/html; charset=utf-8")
		self.end_headers()
		self.wfile.write('hello'.encode())

myServer = HTTPServer((hostName, hostPort), MyServer)

print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))