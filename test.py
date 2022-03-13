from h import *

def how_to_run(filename,start_time):
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
				from py_compile import compile
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

def cmp():
	start_time='11111'
	# signal.signal(signal.SIGINT, signal.SIG_IGN)
	while 1:
		p='2222'
		try:
			c=[how_to_run(w,start_time) for w in argv[1:]]
			r=[]
			for w in c:
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
# assert(0)
if len(argv)==2:

	cmp()
else:
	assert(0)
