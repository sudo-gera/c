''':'
python3 $0 $@
exit
':'''





def __lancom__():
	class real_server:
		def run_server(server_self,myServer):
			try:
				myServer.serve_forever()
			except:
				print('server_stop')
				myServer.server_close()

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
				ret=server_self.call(path,data,server_self)

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
			from time import time
			server_self.id=int(time()*2**64)
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
			server_to_run=ThreadingSimpleServer
			# server_to_run=HTTPServer
			st=1
			while st:
				try:
					myServer = server_to_run((hostName, hostPort), MyServer)
					st=0
				except:
					if port==None:
						hostPort+=1
					else:
						BaseException(f'port {port} is used')
			server_self.port=hostPort
			from threading import Thread as bg
			# from multiprocessing import Process as bg
			server_self.ms=MyServer
			server_self.bg=bg(target=partial(server_self.run_server,myServer))
			server_self.bg.start()

	qs=[]
	def call(qs,path,data,server_self):
		from queue import Queue
		from json import loads,dumps
		try:
			if path.startswith('get'):
				path=int(path[3:])
				return qs[path].get()
			elif path.startswith('put'):
				path=int(path[3:])
				qs[path].put(data)
				return data
			elif path.startswith('has'):
				path=int(path[3:])
				return dumps(qs[path].qsize())
			elif path.startswith('id'):
				return dumps(server_self.id)
			elif path.startswith('new'):
				path=int(path[3:])
				qs.append(Queue())
				qs.append(Queue())
				d=Connection('127.0.0.1:'+str(server.port),len(qs)-1,len(qs)-2,path)
				auto_connected.append(d)
				if hasattr(userver,'on_connection'):
					try:
						userver.on_connection(d)
					except:
						from traceback import format_exc 
						from sys import stderr
						print(format_exc(),file=stderr)
				return dumps([len(qs)-2,len(qs)-1])
			elif path.startswith('kill'):
				raise KeyboardInterrupt
		except KeyboardInterrupt:
			raise KeyboardInterrupt
		except:
			from traceback import format_exc
			from sys import stderr
			print(format_exc(),file=stderr)
	from functools import partial
	call=partial(call,qs)


	server=real_server(call=call)
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
		return server.port
	# get_port=partial(get_port,server)


	def req(q='',w='',e=get_port,url='http://127.0.0.1:'+str(get_port())+'/'):
		from json import loads,dumps
		from urllib.request import urlopen
		if e==get_port:
			return loads(urlopen(str(url)+str(q)+str(w)).read().decode())
		else:
			return loads(urlopen(str(url)+str(q)+str(w),data=dumps(e).encode()).read().decode())

	def get_ips():
		from os import popen
		a=['ifconfig','ipconfig','ip a','wsl ifconfig','wsl ip a','wine ipconfig']
		a=[[w+' 2>&1'] for w in a]
		for w in a:
			try:
				w[0]=popen(w[0]).read()
			except:
				w[0]=''
		a=sum(a,[])
		a=' '+' '.join(a)+' 127.0.0.1 '
		# a=' '+popen('ifconfig 2>&1').read()+' '+popen('ip a 2>&1').read()+' '+popen('ipconfig 2>&1').read()+' '+popen('wine ipconfig 2>&1').read()+' 127.0.0.1 '
		import re
		a=re.findall(r'\s\d+\.\d+\.\d+\.\d+\s',a)
		a=[w.strip() for w in a]
		a=[w for w in a if all([int(e)<256 for e in w.split('.')])]
		from functools import reduce
		a.sort()
		a=reduce(lambda a,s:a if a and a[-1]==s else a+[s],a,[])
		a=[w+':'+str(get_port()) for w in a]
		a=[[w] for w in a]
		from urllib.request import urlopen
		rid=req('id')
		for w in a:
			try:
				t=req('id',url=makeurl(w[0]))
				if rid!=t:
					w.pop()
			except:
				w.pop()
		a=sum(a,[])
		from difflib import ndiff
		a.sort(key=lambda a:len(list(filter(lambda a:a.startswith(' '),ndiff(a,'127.0.0.1:'+str(get_port()))))),reverse=1)
		return a

	def stop_connections():
		# try:
		# 	req('kill')
		# except:
		# 	pass
		try:
			server.ms.server_close()
		except:
			pass
		try:
			server.bg.join()
		except:
			pass

	auto_connected=[]

	class Connection:
		def __init__(s,q,w=None,e=None,r=None):
			q=makeurl(q)
			s.serverurl=q
			if w==None:
				w,e=req('new',req('id'),url=s.url)
				r=req('id',url=s.url)
			s.r2s=w
			s.s2r=e
			s.id=r
			from queue import Queue
			s.gq=Queue()
			from threading import Thread
			s.bg=Thread(target=s._autoget)
			s.bg.start()

		def has(s):
			return req('has',s.r2s,url=s.url)

		def get(s):
			return s.gq.get()

		def put(s,d):
			return req('put',s.s2r,d,url=s.url)

		def _autoget(s):
			while 1:
				try:
					d=req('get',s.r2s,url=s.url)
					if hasattr(s,'on_message'):
						s.on_message(d)
					else:
						s.gq.put(d)
				except:
					from traceback import format_exc
					from sys import stderr
					print(format_exc(),file=stderr)

	class user_server:
		@property
		def id(s):
			return s._id
		@property
		def ip(s):
			return s._ip()
		@property
		def connected(s):
			return s._connected[:]

	userver=user_server()
	userver._id=req('id')
	userver._ip=get_ips	
	userver._connected=auto_connected

	return userver,Connection

server,connect=__lancom__()
del(__lancom__)


