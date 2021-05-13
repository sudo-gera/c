#!/usr/bin/env python3
from sys import argv
from time import *
from sys import executable
from subprocess import run as subrun
from pathlib import Path
from traceback import format_exc
from os.path import exists
from os.path import expanduser
from os.path import isdir
from os.path import dirname
from os.path import normpath
from os.path import abspath
from os import listdir
from os import getenv
from os import getpid
from importlib.util import spec_from_file_location
from importlib.util import module_from_spec
from threading import Thread
from multiprocessing import Process
from http.server import BaseHTTPRequestHandler, HTTPServer
from signal import SIGKILL
from os import kill
from urllib.request import urlopen
try:
	from watchdog.observers import Observer
	from watchdog.events import FileSystemEventHandler
except:
	c=0
	try:
		subrun([executable,'-m','pip','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun(['pip3','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun(['python3-pip','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun(['python-pip','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun(['pip','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun([dirname(executable)+'/pip','install','watchdog'])
		c=1
	except:
		print(format_exc())
	try:
		subrun([dirname(executable)+'/pip3','install','watchdog'])
		c=1
	except:
		print(format_exc())
	if c==0:
		print('looks like installation failed, try to run:')
		print('\tsudo apt update')
		print('\tsudo apt -f install')
		print('\tsudo apt install python3-pip')
		print('and then run this file again')
	from watchdog.observers import Observer
	from watchdog.events import FileSystemEventHandler

home=str(Path.home())+'/'

if argv:
	subrun(['chmod','777',__file__])
	# path=getenv('PATH')
	# if path==None or normpath(dirname(__file__)) not in sum([[abspath(w),normpath(w)] for w in path.split(':')],[]):
	# 	print('copy this file to PATH')
	# 	print('you can copy it to any of this directries:')
	# 	for w in path.split(':'):
	# 		print('\t'+w)
	# 	if argv:
	# 		print('to copy run command:')
	# 		print('')
	# 	print('or you can add line to rc file of your shell')
	# 	print(f'PATH="$PATH:{dirname(__file__)}"')

import json
import binascii
def dump(a):
	a=json.dumps(a)
	a=a.encode()
	a=binascii.hexlify(a)
	a=a.decode()
	return a
def load(a):
	a=a.encode()
	a=binascii.unhexlify(a)
	a=a.decode()
	a=json.loads(a)
	return a

sidedef='''
#instructions how to run different files
#return format: array of comands, each comand is array with executable and arguments
def execute(filename):
	if filename.endswith('.py'):
		return [
			['python3',filename]
		]
	if filename.endswith('.rb'):
		return [
			['ruby',filename]
		]
	if filename.endswith('.js'):
		return [
			['node',filename]
		]
	if filename.endswith('.cpp'):
		return [
			['g++','-Wfatal-errors',filename],
			['a.out']
		]
'''

class Handler(FileSystemEventHandler):
	def run(self,event,mul=1):
		if mul:
			Process(target=self.run,args=(event,0)).start()
			return
		global sidedef
		if not event.is_directory:
			if not exists(home+'.side.py'):
				open(home+'.side.py','w').write(sidedef)
			file=str(event.src_path)
			if file.endswith('.stdin'):
				file=file[:-6]
			open(file+'.stdout','w').close()
			with open(file+'.stdout','a') as a:
				_a=[]
				try:
					exec(open(home+'.side.py').read()+'\n_a.append(execute)')
					ex=_a[0]
				except:
					print('failed to exec ~/.side.py',file=a)
					print(format_exc(),file=a)
				ex=ex(file)
				if ex==None:
					print('file ~/.side.py has no instructions for running',file,file=a)
					print('if you want to add instructions, edit ~/.side.py',file=a)
				else:
					urlopen(f'http://{hostname}:{hostport}/{dump(["start",file,getpid()])}').read()
					print(f'||| execution start at {(str(time())+"0"*20)[:20]} ({asctime()})',file=a)
					a.flush()
					for w in ex:
						if subrun(w,stdin=open(file+'.stdin'),stdout=open(file+'.stdout','a'),stderr=open(file+'.stdout','a')).returncode:
							break
					if open(file+'.stdout').read()[-1]!='\n':
						print(file=a)
					print(f'||| execution stop  at {(str(time())+"0"*20)[:20]} ({asctime()})',file=a)
					urlopen(f'http://{hostname}:{hostport}/{dump(["stop",file,getpid()])}').read()
			a.close()
	on_created=on_deleted=on_moved=on_modified=run

class ev:
	def __init__(s,src_path):
		s.src_path=src_path
		s.is_directory=False

obss=[]


hostname = '127.0.0.1'
hostport = 14267


def runserver():
	pids={}
	class MyServer(BaseHTTPRequestHandler):
		def do_GET(self):
			path=self.path[1:]
			path=load(path)
			self.send_response(200)
			self.send_header("Content-type", "text/html; charset=utf-8")
			self.end_headers()
			if path[0]=='start':
				if path[1] in pids:
					kill(pids[path[1]],SIGKILL)
				pids[path[1]]=path[2]
			elif path[0]=='stop':
				if path[1] in pids:
					del(pids[path[1]])
			elif path[0]=='exit':
				for w in pids:
					kill(pids[w],SIGKILL)
				raise KeyboardInterrupt	
			# self.wfile.write('hello'.encode())
		def log_message(self, *args):
			return

	try:
		myServer = HTTPServer((hostname, hostport), MyServer)
	except:
		pass

	try:
	    myServer.serve_forever()
	except KeyboardInterrupt:
	    pass

	myServer.server_close()



def update():
	urlopen(f'http://{hostname}:{hostport}/{dump(["start","update",getpid()])}').read()
	try:
		a=urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/side.py').read().decode()
		open(__file__,'w').write(a)
	except:
		pass
	urlopen(f'http://{hostname}:{hostport}/{dump(["stop","update",getpid()])}').read()



if __name__ == '__main__':
	observer=Process(target=runserver)
	observer.start()
	obss.append(observer)
	observer=Process(target=update)
	observer.start()
	obss.append(observer)
	if len(argv)<2:
		print('nothing to track')
		sleep(0.1)
	else:
		for file in argv[1:]:
			if not exists(file):
				open(file,'w')
			if not exists(file+'.stdin'):
				open(file+'.stdin','w')
			subrun(['subl',file])
			subrun(['subl',file+'.stdin'])
			subrun(['subl',file+'.stdout'])
			observer=Thread(target=Handler().run,args=(ev(file),))
			observer.start()
			obss.append(observer)
			observer = Observer()
			observer.schedule(Handler(), path=file, recursive=True)
			observer.start()
			obss.append(observer)
			observer = Observer()
			observer.schedule(Handler(), path=file+'.stdin', recursive=True)
			observer.start()
			obss.append(observer)
		print('started tracking:')
		print(*argv[1:])
		print('press enter to stop')
		try:
			input()
		except KeyboardInterrupt:
			print()
	# print('exiting, wait 4 seconds... press ctrl+c then enter if you are waiting more than 4 seconds')
	urlopen(f'http://{hostname}:{hostport}/{dump(["exit"])}').read()
	for observer in obss:
		try:
			observer.stop()
		except:
			pass
		observer.join()