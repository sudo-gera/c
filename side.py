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

class Handler(FileSystemEventHandler):
	def run(self,event):
		if not event.is_directory:
			if not exists(home+'.side'):
				open(home+'.side','w').write('def execute(filename):\n\tpass\n')
			try:
				file=event.src_path
				if file.endswith('.stdin'):
					file=file[:-6]
				a=[]
				exec(open(home+'.side').read()+'\na.append(execute)')
				ex=a[0]
				ex=ex(file)
				open(file+'.stdout','w')
				for w in ex:
					if run(w,stdin=open(file+'.stdin'),stdout=open(file+'.stdout','a'),stderr=open(file+'.stdout','a')).returncode:
						break
			except:
				print('failed to exec ~/.side:\n'+format_exc())
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

try:
	while True:
		sleep(0.1)
except KeyboardInterrupt:
	pass

print()

for observer in obss:
	observer.stop()
	observer.join()