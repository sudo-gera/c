#!/usr/bin/env python3
from sys import argv
from time import *
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from subprocess import run as subrun
from pathlib import Path
from traceback import format_exc
from os.path import exists
from importlib.util import spec_from_file_location
from importlib.util import module_from_spec
home=str(Path.home())+'/'

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
	def run(self,event):
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
					print(f'||| execution start at {(str(time())+"0"*20)[:20]} ({asctime()})',file=a)
					a.flush()
					for w in ex:
						if subrun(w,stdin=open(file+'.stdin'),stdout=open(file+'.stdout','a'),stderr=open(file+'.stdout','a')).returncode:
							break
					if open(file+'.stdout').read()[-1]!='\n':
						print(file=a)
					print(f'||| execution stop  at {(str(time())+"0"*20)[:20]} ({asctime()})',file=a)
			a.close()
	on_created=on_deleted=on_moved=on_modified=run

class ev:
	def __init__(s,src_path):
		s.src_path=src_path
		s.is_directory=False

obss=[]

for file in argv[1:]:
	if not exists(file):
		open(file,'w')
	if not exists(file+'.stdin'):
		open(file+'.stdin','w')
	Handler().run(ev(file))
	subrun(['subl',file])
	observer = Observer()
	observer.schedule(Handler(), path=file, recursive=True)
	observer.start()
	obss.append(observer)
	subrun(['subl',file+'.stdin'])
	observer = Observer()
	observer.schedule(Handler(), path=file+'.stdin', recursive=True)
	observer.start()
	obss.append(observer)
	subrun(['subl',file+'.stdout'])

print('started tracking:')
print(*argv[1:])
print('press enter to stop')
# try:
# 	while True:
# 		sleep(0.01)
# except KeyboardInterrupt:
# 	print()
# 	print('exiting...')
input()
print('exiting...')
# print()

for observer in obss:
	observer.stop()
	observer.join()