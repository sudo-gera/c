def bg_run(f):
	from threading import Thread
	Thread(target=f).start()

@bg_run
def run_server_thread(port=9999):
	send_q=[]
	read_q=[]
	from http.server import BaseHTTPRequestHandler, HTTPServer
	class MyServer(BaseHTTPRequestHandler):
		def do_GET(self):
			path=self.path
			
			self.send_response(200)
			self.send_header("Content-type", "text/html; charset=utf-8")
			self.end_headers()
			self.wfile.write(ret.encode())
		def log_message(*a):
			pass
	hostname = '0.0.0.0'
	hostport = port
	st=1
	while st:
		try:
			myServer = HTTPServer((hostname, hostport), MyServer)
			st=0
		except:
			hostport+=1
	try:
		myServer.serve_forever()
	except KeyboardInterrupt:
		pass
	myServer.server_close()

from time import *


