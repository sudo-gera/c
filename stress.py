def create_input_string(q):
	from subprocess import run,PIPE
	return run(['python3','create_input.py',str(q)],stdout=PIPE).stdout.decode()

TIME_LIMIT=4
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
from json import *

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
			if run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address,undefined,float-divide-by-zero,float-cast-overflow','-g',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.c'):
			if run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address,undefined,float-divide-by-zero,float-cast-overflow','-g',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.py'):
			if run(['python3','-m','py_compile',filename]).returncode:
				print(file=stderr)
				exit()
			try:
				compile(filename,cfile=compiled_file,optimize=0,doraise=True)
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

def cmp(log,start_time,stop,pr_num):
	signal.signal(signal.SIGINT, signal.SIG_IGN)
	counter=pr_num
	while 1:
		try:
			p=create_input_string(counter)
			counter+=PROCESS_COUNT
		except Exception:
			log.put([format_exc()])
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
				w=w.stdout.read().decode()
				r.append(w)
			c=r
			if run(['python3','is_equal.py'],input=dumps([p]+c).encode()).returncode:
			# sc=set(c)
			# if len(sc)!=1:
				log.put([p,'different output'])
			else:
				log.put(None)
		except Exception:
			log.put([p,format_exc()])
			exit()
		except:
			break

def logging(log,stop):
	signal.signal(signal.SIGINT, signal.SIG_IGN)
	c=0
	t=time()
	while 1:
		try:
			q=log.get()
		except KeyboardInterrupt:
			exit()
		if not stop.empty():
			break
		if type(q)==list and len(q)==2:
			print('\r                                                   \r',end='')
			print('\x1b[91mERROR\x1b[0m')
			print(q[1])
			open('created_input.txt','w').write(q[0])
			print('\x1b[94minput saved to created_input.txt\x1b[0m')
			print()
			stop.put('stop')
			exit()
		if type(q)==list and len(q)==1:
			print('\r                                                   \r',end='')
			print('\x1b[91mERROR\x1b[0m')
			print(q[0])
			print()
			stop.put('stop')
			exit()
		elif q==None:
			c+=1
			y=time()
			if y-t>0.8:
				print(f'   {c} sucessfull tests',end='\r')
				t=y
		else:
			print('\r                                                   \r',end='')
			print('\x1b[91mERROR: wrong log\x1b[0m')
			exit()


if __name__=='__main__':
	assert TIME_LIMIT
	# if len(argv)<3:
	# 	raise\
	# 		ValueError('need at least 2 files to compare, got '+str(len(argv)-1))
	log=Queue()
	stop=Queue()
	[how_to_run(w,start_time,stop,log) for w in argv[1:]]

	a=Process(target=logging,args=(log,stop))
	a.start()
	s=[]
	d=4
	pr_num=0
	for w in range(PROCESS_COUNT):
		if not stop.empty():
			break
		s.append(Process(target=cmp,args=(log,start_time,stop,pr_num)))
		pr_num+=1
		s[-1].daemon = True
		s[-1].start()
		if d:
			try:
				st=0
				while st<TIME_LIMIT:
					sleep(0.2)
					if not stop.empty():
						break
					st+=0.2
			except KeyboardInterrupt:
				print()
				stop.put('stop')
				log.put(None)
			d-=1
	try:
		a.join()
	except KeyboardInterrupt:
		print()
	except SystemExit:
		pass
	stop.put('stop')
	not_print=0
	if all([not w.is_alive() for w in s]):
		not_print=1
	for w in range(TIME_LIMIT*10):
		if all([not w.is_alive() for w in s]):
			break
		w=round(w*8/TIME_LIMIT)
		print('exiting:','#'*w+'-'*(80-w),end='\r')
		sleep(0.2)
	for w in s:
		w.terminate()
	system('rm -fr tmp*.trash.trash.*')
	if not_print==0:
		print('exiting:','#'*80+'-'*(80-80),end='\r')
		sleep(0.2)
	print('        ',' '*80+' '*(80-80),end='\r')
