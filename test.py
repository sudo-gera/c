''':'
python3 $0 $@
exit
':'''


try:
	from icecream import ic
except:
	ic=print


class Server:
	class running:
		def __init__(s,ms):
			s.ms=ms

		def __enter__(s):
			return s

		def __exit__(s):
			ic()
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
				self.send_header('Access-Control-Allow-Origin', '*')
				self.end_headers()
				self.wfile.write(ret)

			def do_POST(self):
				global admin
				lenn=int(self.headers['Content-Length'])
				data=self.rfile.read(lenn)
				ret,ct=server_self.do(self,data)
				self.send_response(200)
				self.send_header("Content-type", ct)
				self.send_header("Access-Control-Allow-Origin", '*')
				self.end_headers()
				self.wfile.write(ret)

			def log_message(*a):
				pass

		if port!=None:
			hostPort=port
		else:
			hostPort=port=1234
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
		server_self.port=hostPort
		from threading import Thread
		server_self.thread=Thread(target=partial(server_self.run_server,myServer))
		server_self.thread.start()


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
	from difflib import ndiff
	a.sort(key=lambda a:len(list(filter(lambda a:a.startswith(' '),ndiff(a,'127.0.0.1')))),reverse=1)
	return a

