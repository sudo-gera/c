def create_input_string():
	from subprocess import run,PIPE
	return run(['python3','create_input.py'],stdout=PIPE).stdout.decode()

TIME_LIMIT=2
PROCESS_COUNT=16

from time import time,perf_counter
start_time=str(int(time()*2**128)+int(perf_counter()*2**64))

from multiprocessing import Pool,Queue,Process
from os import system
from os.path import exists
from py_compile import compile,PyCompileError
from queue import Queue as bq
from subprocess import run,PIPE,Popen,TimeoutExpired
from sys import argv,executable
from time import sleep,time, asctime
from traceback import format_exc
import signal
from sys import stderr
from ast import parse

def how_to_run(filename,start_time,stop,log):
	compiled_file='./tmp'+start_time+'_'+filename.replace('/','_')+'_.trash.trash'
	if filename.endswith('.cpp'):
		compiled_file+='.out'
	if filename.endswith('.c'):
		compiled_file+='.out'
	if filename.endswith('.py'):
		compiled_file+='.py'
	if filename.endswith('.out'):
		compiled_file+='.out'
	if not exists(compiled_file):
		if filename.endswith('.cpp'):
			if run(['g++','-Ofast','-lgmpxx','-lgmp','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.c'):
			if run(['g++','-Ofast','-lgmpxx','-lgmp','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.py'):
			if run(['python3','-m','py_compile',filename]).returncode:
				print(file=stderr)
				exit()
			try:
				compile(filename,cfile=compiled_file,optimize=2,doraise=True)
			except Exception:
				print(format_exc(),stderr)
				exit()
		if filename.endswith('.out'):
			if run(['cp',filename,compiled_file]).returncode:
				exit()
	if filename.endswith('.cpp'):
		return [compiled_file]
	if filename.endswith('.c'):
		return [compiled_file]
	if filename.endswith('.py'):
		return [executable,compiled_file]
	if filename.endswith('.out'):
		return [compiled_file]

def cmp(log,start_time,stop):
	signal.signal(signal.SIGINT, signal.SIG_IGN)
	while 1:
		try:
			p=create_input_string()
		except:
			log.put(['',''])
			exit()
		try:
			if not stop.empty():
				break
			c=[how_to_run(w,start_time,stop,log) for w in argv[1:]]
			r=[]
			for w in c:
				if not stop.empty():
					break
				rr=time()
				try:
					w=Popen(w,stdout=PIPE,stdin=PIPE)
				except Exception:
					log.put([p,format_exc()])
					exit()
				w.stdin.write(p.encode())
				w.stdin.close()
				try:
					if w.wait(TIME_LIMIT):
						w.terminate()
						log.put([p,'non-zero run code'])
						exit()
				except TimeoutExpired:
					w.terminate()
					log.put([p,'time limit'])
					exit()
				w=w.stdout.read()
				r.append(w)
			c=r
			sc=set(c)
			if len(sc)!=1:
				log.put([p,'different output'])
			else:
				log.put(None)
		except Exception:
			log.put([p,format_exc()])
			exit()
		except:
			break

def logging(log,stop):
	c=0
	t=time()
	while 1:
		if not stop.empty():
			break
		try:
			q=log.get()
		except KeyboardInterrupt:
			exit()
		if type(q)==list:
			print('\x1b[91mERROR\x1b[0m')
			print('\x1b[94minput(str version)\x1b[0m')
			print(str(q[0]))
			print('\x1b[94minput(repr version)\x1b[0m')
			print(repr(q[0]))
			print('\x1b[91mWHAT:\x1b[0m')
			print(q[1])
			print()
			exit()
			stop.put('stop')
		elif q==None:
			c+=1
			y=time()
			if y-t>1:
				print(f'{c} sucessfull tests')
				t=y
		else:
			print('\x1b[91mERROR: wrong log\x1b[0m')
			exit()


if __name__=='__main__':
	assert TIME_LIMIT
	if len(argv)<3:
		raise\
			ValueError('need at least 2 files to compare, got '+str(len(argv)-1))
	log=Queue()
	stop=Queue()
	[how_to_run(w,start_time,stop,log) for w in argv[1:]]

	a=Process(target=logging,args=(log,stop))
	a.start()
	s=[]
	for w in range(PROCESS_COUNT):
		s.append(Process(target=cmp,args=(log,start_time,stop)))
		s[-1].daemon = True
		s[-1].start()
	try:
		a.join()
	except KeyboardInterrupt:
		print('\r  \r',end='')
	except SystemExit:
		pass
	stop.put('stop')
	for w in range(TIME_LIMIT*10):
		w=round(w*8/TIME_LIMIT)
		print('exiting:','#'*w+'-'*(80-w),end='\r')
		sleep(0.2)
		if all([not w.is_alive() for w in s]):
			break
	for w in s:
		w.terminate()
	system('rm -fr tmp*.trash.trash.*')
	print('exiting:','#'*80+'----'*(80-80),end='\r')
	sleep(0.2)
	print('        ','    '*80+'    '*(80-80),end='\r')
