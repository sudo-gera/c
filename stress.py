def create_input_string():
	from subprocess import run,PIPE
	return run(['python3','create_input.py'],stdout=PIPE).stdout.decode()

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
			if run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.c'):
			if run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode:
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
<<<<<<< HEAD
		from time import time
		t='./tmp'+str(time())+'.trash.trash'
		return [['g++','-std=c++17','-Wfatal-errors','-g',filename,'-o',t],['valgrind','--leak-check=full',t],['rm',t]]
	if filename.endswith('.c'):
		from time import time
		t='./tmp'+str(time())+'.trash.trash'
		return [['cc',              '-Wfatal-errors','-g',filename,'-o',t],['valgrind','--leak-check=full',t],['rm',t]]
=======
		return [compiled_file]
	if filename.endswith('.c'):
		return [compiled_file]
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	if filename.endswith('.py'):
		return [executable,compiled_file]
	if filename.endswith('.out'):
		return [compiled_file]

def cmp(log,start_time,stop):
	signal.signal(signal.SIGINT, signal.SIG_IGN)
	while 1:
<<<<<<< HEAD
		from sys import argv
		from subprocess import run,PIPE
		c=[how_to_run(w) for w in argv[1:]]
		p=create_input_string()
		c=[[run(e,stdout=PIPE,stderr=PIPE,input=p.encode()) for e in w] for w in c]
		if any([any([e.returncode for e in w]) for w in c]):
			log.put([p])
		c=[['\n'.join([r.strip() for r in (e.stdout.decode() if hasattr(e,'stdout') and e.stdout!=None else '').strip().split('\n') if r.strip()])+\
			'\n'.join([r.strip() for r in ([e.stderr.decode(),''][-1] if hasattr(e,'stderr') and e.stderr!=None else '').strip().split('\n') if r.strip()])
			for e in w] for w in c]
		c=[''.join(w) for w in c]
		sc=set(c)
		if len(sc)!=1:
			log.put([p,c])
		else:
			log.put(None)
=======
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
				try:
					w=Popen(w,stdout=PIPE,stdin=PIPE)
				except Exception:
					log.put([p,format_exc()])
					exit()
				w.stdin.write(p.encode())
				w.stdin.close()
				try:
					if w.wait(2):
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
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a

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
	if len(argv)<3:
		raise\
			ValueError('need at least 2 files to compare, got '+str(len(argv)-1))
	log=Queue()
	stop=Queue()
	[how_to_run(w,start_time,stop,log) for w in argv[1:]]

	a=Process(target=logging,args=(log,stop))
	a.start()
	s=[]
	for w in range(16):
		s.append(Process(target=cmp,args=(log,start_time,stop)))
		s[-1].daemon = True
		s[-1].start()
	try:
		a.join()
	except KeyboardInterrupt:
		print()
	except SystemExit:
		pass
	stop.put('stop')
	print('exiting...')
	for w in range(20):
		print('####'*w+'----'*(20-w),end='\r')
		sleep(0.2)
	for w in s:
		w.terminate()
	system('rm -fr tmp*.trash.trash.*')
	print('####'*20+'----'*(20-20),end='\r')
	sleep(0.2)
	print('    '*20+'    '*(20-20),end='\r')
