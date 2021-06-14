def bg_run(f):
	from threading import Thread
	Thread(target=f,args=(func,)).start()

def get_ips():
	return ['127.0.0.1']

class connecton:
	def __init__(conn,url):
		conn.url=url
		conn.id=time()
		conn.port=19855
		conn.data(conn.url,{'act':'new','ips':get_ips(),'id':conn.id})

	def data(conn,addr,mess):
		from json import dumps
		mess=dumps(mess)
		mess=mess.encode()
		from urllib.request import urlopen
		mess=urlopen(addr,data=mess)
		from json import loads
		mess=loads(mess)
		return mess

	def send_message(conn,mess):
		return conn.data(conn.url,{'act':'send','data':mess})

	def get_messages(conn):
		return conn.data('http://127.0.0.1:'+str(conn.port),{'act':'get'})
		
@bg_run
def run_server_thread(func,port=9999):
	server_id=time()
	messages=[]
	connectons=[]
	from http.server import BaseHTTPRequestHandler, HTTPServer
	class MyServer(BaseHTTPRequestHandler):
		def do_POST(self):
			lenn=int(self.headers['Content-Length'])
			data=self.rfile.read(lenn)
			data=data.decode()
			from json import dumps
			ret=dumps(None)
			if data['act']=='send':
				messages.append(data['data'])
			elif data['act']=='exit':
				raise KeyboardInterrupt
			elif data['act']=='new':
				pass
			elif data['act']=='get':
				ret=dumps(messages)
				messages=[]
			elif data['act']=='getid':
				ret=dumps(server_id)
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


