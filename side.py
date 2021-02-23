#!/usr/bin/env python3
from sys import argv
from time import sleep
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from subprocess import run
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
			try:
				file=event.src_path
				if file.endswith('.stdin'):
					file=file[:-6]
				a=[]
				exec(open(home+'.side.py').read()+'\na.append(execute)')
				ex=a[0]
				ex=ex(file)
				if ex==None:
					print('file ~/.side.py has no instructions for running',file)
					print('if you want to add instructions, edit ~/.side.py')
				else:
					open(file+'.stdout','w')
					for w in ex:
						if run(w,stdin=open(file+'.stdin'),stdout=open(file+'.stdout','a'),stderr=open(file+'.stdout','a')).returncode:
							break
			except:
				print('failed to exec ~/.side.py')
				print(format_exc())
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
	run(['subl',file])
	observer = Observer()
	observer.schedule(Handler(), path=file, recursive=True)
	observer.start()
	obss.append(observer)
	run(['subl',file+'.stdin'])
	observer = Observer()
	observer.schedule(Handler(), path=file+'.stdin', recursive=True)
	observer.start()
	obss.append(observer)
	run(['subl',file+'.stdout'])

print('started tracking:')
print(*argv[1:])
print('press ctrl+c to stop')
try:
	while True:
		sleep(0.1)
except KeyboardInterrupt:
	pass

print()

for observer in obss:
	observer.stop()
	observer.join()