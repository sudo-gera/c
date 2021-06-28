''':'
python3 $0 $@
exit
':'''





class lancom:
	class Server:
		class running:
			def __init__(s,ms):
				s.ms=ms

			def __enter__(s):
				return s

			def __exit__(s):
				myServer.server_close()

		def run_server(server_self,myServer):
			with server_self.running(myServer) as d:
				d.ms.serve_forever()

		def do(server_self,self,data=None):
			path=self.path
			if path[0]!='/':
				print('unexpected path: ',path)
			else:
				path=path[1:]

			
			if server_self.call==None:
				server_self.s2u.put([path,data])
				ret=server_self.u2s.get()
			else:
				ret=server_self.call(path,data)

			ct='file/file'
			while type(ret)!=bytes:
				if type(ret)==str:
					ret=ret.encode()
					ct="text/html; charset=utf-8"
				elif type(ret)==bytearray:
					ret=bytes(ret)
				else:
					ret=repr(ret)
			return ret,ct


		def __bool__(s):
			return s.has()



		def __init__(server_self,call=None,port=None,):
			server_self.call=call
			from queue import Queue
			server_self.u2s=Queue()
			server_self.s2u=Queue()
			server_self.get=server_self.s2u.get
			server_self.put=server_self.u2s.put
			server_self.has=lambda :bool(server_self.s2u.qsize())
			from http.server import BaseHTTPRequestHandler, HTTPServer
			import time
			from urllib.request import urlopen as u
			from urllib.parse import unquote as uqu
			from json import loads as l
			from sys import argv
			import os
			import random
			from functools import partial
			from socketserver import ThreadingMixIn
			class MyServer(BaseHTTPRequestHandler):
				def do_GET(self):
					ret,ct=server_self.do(self)
					self.send_response(200)
					self.send_header("Content-type", ct)
					self.end_headers()
					self.wfile.write(ret)

				def do_POST(self):
					global admin
					lenn=int(self.headers['Content-Length'])
					data=self.rfile.read(lenn)
					ret,ct=server_self.do(self,data)
					self.send_response(200)
					self.send_header("Content-type", ct)
					self.end_headers()
					self.wfile.write(ret)

				def log_message(*a):
					pass

			if port!=None:
				hostPort=port
			else:
				hostPort=12345
			hostName='0.0.0.0'
			class ThreadingSimpleServer(ThreadingMixIn, HTTPServer):
			    pass
			st=1
			while st:
				try:
					myServer = ThreadingSimpleServer((hostName, hostPort), MyServer)
					st=0
				except:
					if port==None:
						hostPort+=1
					else:
						BaseException(f'port {port} is used')
			server_self.port=hostPort
			from threading import Thread
			server_self.thread=Thread(target=partial(server_self.run_server,myServer))
			server_self.thread.start()

	qs=[]
	def call(qs,path,data):
		from queue import Queue
		from json import loads,dumps
		try:
			if path.startswith('get'):
				path=int(path[3:])
				return qs[path].get()
			elif path.startswith('put'):
				path=int(path[3:])
				qs[path].put(data)
				return dumps(None)
			elif path.startswith('has'):
				path=int(path[3:])
				return dumps(qs[path].qsize())
			elif path.startswith('new'):
				qs.append(Queue())
				qs.append(Queue())
				auto_connected.append(Connection('127.0.0.1:'+str(server.port),len(qs)-1,len(qs)-2))
				return dumps([len(qs)-2,len(qs)-1])
		except:
			from traceback import format_exc
			print(format_exc())
		from functools import partial
		call=partial(call,qs)


	server=Server(call=call)
	# print(server.port)

	def makeurl(q):
		q=q.strip()
		for w in range(len('http://')):
			if q.startswith('http://'[w:]):
				q='http://'[:w]+q
			if q.startswith('https://'[w:]):
				q='https://'[:w]+q
		if not q.startswith('http://') and not q.startswith('https://'):
			q='http://'+q
		if q[-1:]!='/':
			q+='/'
		return q


def get_port():
	return lancom.server.port

def get_ips():
	from os import popen
	a=popen('ifconfig 2>&1').read().split()+popen('ipconfig 2>&1').read().split()
	a=[a[w:w+2] for w in range(len(a))]
	a=[w[1] for w in a if w[0].lower()=='inet']
	return a

auto_connected=[]

class Connection:
	def __init__(s,q,w=None,e=None):
		q=lancom.makeurl(q)
		s.url=q
		if w==None:
			w,e=s.req('new')
		s.r2s=w
		s.s2r=e

	def req(s,q,w=None,e=None):
		from json import loads,dumps
		from urllib.request import urlopen
		if w==None:
			return loads(urlopen(s.url+str(q)).read().decode())
		elif e==None:
			return loads(urlopen(s.url+str(q)+str(w)).read().decode())
		else:
			return loads(urlopen(s.url+str(q)+str(w),data=dumps(e).encode()).read().decode())

	def get(s):
		return s.req('get',s.r2s)

	def has(s):
		return s.req('has',s.r2s)

	def put(s,d):
		return s.req('put',s.s2r,d)






