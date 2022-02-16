def create_input_string():
	from subprocess import run,PIPE
	return run(['python3','create_input.py'],stdout=PIPE).stdout.decode()

from time import time,perf_counter
start_time=str(int(time()*2**128)+int(perf_counter()*2**64))

def how_to_run(filename):
	compiled_file='./tmp'+start_time+'_'+filename.replace('/','_')+'_.trash.trash'
	if filename.endswith('.cpp'):
		compiled_file+='.out'
	if filename.endswith('.c'):
		compiled_file+='.out'
	if filename.endswith('.py'):
		compiled_file+='.pyc'
	if filename.endswith('.out'):
		compiled_file+='.out'
	from os.path import exists
	from subprocess import run
	if not exists(compiled_file):
		if filename.endswith('.cpp'):
			assert run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode==0
		if filename.endswith('.c'):
			assert run(['g++','-Ofast','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode==0
			# assert run(['cc','-Ofast','-std=c17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',compiled_file]).returncode==0
		if filename.endswith('.py'):
			from py_compile import compile
			compile(filename,cfile=compiled_file,optimize=2,doraise=True)
		if filename.endswith('.out'):
			assert run(['cp',filename,compiled_file]).returncode==0
	if filename.endswith('.cpp'):
		return [[compiled_file]]
	if filename.endswith('.c'):
		return [[compiled_file]]
	if filename.endswith('.py'):
		from sys import executable
		return [[executable,compiled_file]]
	if filename.endswith('.out'):
		return [[compiled_file]]

def cmp(log):
	from time import time, asctime
	while 1:
		from sys import argv
		from subprocess import run,PIPE
		c=[how_to_run(w) for w in argv[1:]]
		p=create_input_string()
		c=[[run(e,stdout=PIPE,input=p.encode()) for e in w] for w in c]
		if any([any([e.returncode for e in w]) for w in c]):
			log.put([p])
		c=[['\n'.join([r.strip() for r in (e.stdout.decode() if hasattr(e,'stdout') and e.stdout!=None else '').strip().split('\n') if r.strip()])+\
			'\n'.join([r.strip() for r in (e.stderr.decode() if hasattr(e,'stderr') and e.stderr!=None else '').strip().split('\n') if r.strip()])
			for e in w] for w in c]
		c=[''.join(w) for w in c]
		sc=set(c)
		if len(sc)!=1:
			log.put([p,c])
		else:
			log.put(None)

def logging(log):
	c=0
	from time import time
	t=time()
	while 1:
		q=log.get()
		if type(q)==list and len(q)==2:
			q=[q[0]]+q[1]
			print('\x1b[91mERROR\x1b[0m')
			print('\x1b[94minput(str version)\x1b[0m')
			print(str(q[0]))
			print('\x1b[94minput(repr version)\x1b[0m')
			print(repr(q[0]))
			from sys import argv
			for w in range(1,len(argv)):
				print('\x1b[94m'+argv[w]+'(str version)\x1b[0m')
				print(str(q[w]))
				print('\x1b[94m'+argv[w]+'(repr version)\x1b[0m')
				print(repr(q[w]))
			print('\x1b[91mANSWERS ARE DIFFERENT\x1b[0m')
			print()
			exit()
		if type(q)==list and len(q)==1:
			print('\x1b[91mERROR\x1b[0m')
			print('\x1b[94minput(str version)\x1b[0m')
			print(str(q[0]))
			print('\x1b[94minput(repr version)\x1b[0m')
			print(repr(q[0]))
			print('\x1b[91mNON-ZERO RETURN CODE\x1b[0m')
			print()
			exit()
		else:
			c+=1
			y=time()
			if y-t>4:
				print(f'{c} sucessfull tests')
				t=y

if __name__=='__main__':
	if type(create_input_string())!=str:
		raise\
			TypeError('create_input_string() function should return string, not '+type(create_input_string()).__name__)
	from sys import argv
	if len(argv)<3:
		raise\
			ValueError('need at least 2 files to compare, got '+str(len(argv)-1))
	from multiprocessing import Pool,Queue,Process
	log=Queue()

	a=Process(target=logging,args=(log,))
	a.start()
	s=[]
	for w in range(16):
		s.append(Process(target=cmp,args=(log,)))
		s[-1].start()
	try:
		a.join()
	except KeyboardInterrupt:
		pass
	from os import system
	system('rm -fr tmp*.trash.trash.*')
	for w in s:
		w.terminate()
	from time import sleep
	sleep(0.1)
