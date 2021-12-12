def create_input_string():
	from random import randint
	a=[randint(1,9999),randint(1,9999)]
	a.sort()
	a=' '.join([str(w) for w in a])
	a+='\n'
	return a

def how_to_run(filename):
	if filename.endswith('.cpp'):
		from time import time
		t='./tmp'+str(time())+'.trash.trash'
		return [['g++','-std=c++17','-Wfatal-errors','-fsanitize=address','-g',filename,'-o',t],[t],['rm',t]]
	if filename.endswith('.c'):
		from time import time
		t='./tmp'+str(time())+'.trash.trash'
		return [['cc','-Wfatal-errors',filename,'-o',t],[t],['rm',t]]
	if filename.endswith('.py'):
		return [['python3',filename]]
	if filename.endswith('.out'):
		return [[filename]]

def cmp(log):
	from time import time, asctime
	while 1:
		from sys import argv
		from subprocess import run,PIPE
		c=[how_to_run(w) for w in argv[1:]]
		p=create_input_string()
		c=[[run(e,stdout=PIPE,input=p.encode()) for e in w] for w in c]
		c=[['\n'.join([r.strip() for r in (e.stdout.decode() if hasattr(e,'stdout') and e.stdout!=None else '').strip().split('\n') if r.strip()])+\
			'\n'.join([r.strip() for r in (e.stderr.decode() if hasattr(e,'stderr') and e.stderr!=None else '').strip().split('\n') if r.strip()])
			for e in w] for w in c]
		c=[''.join(w) for w in c]
		sc=set(c)
		if len(sc)!=1:
			log.put([p,*c])
		else:
			log.put(None)
		# if len(c)!=1:
		# 	print(p)
		# 	print(c)
		# else:
		# 	if time()-t>4:
		# 		tt=int(time())
		# 		c+=1
		# 		print(f'from {('00'+str((t//3600)%24))[-2:]}:{('00'+str((t//60)%60))[-2:]}:{('00'+str((t//1)%60))[-2:]} to {('00'+str((tt//3600)%24))[-2:]}:{('00'+str((tt//60)%60))[-2:]}:{('00'+str((tt//1)%60))[-2:]} {c} sucessfull tests')
		# 		t=tt
		# 	else:
		# 		c+=1
		# 	print('from ')
		# 	print('ok')

def logging(log):
	c=0
	from time import time
	t=time()
	while 1:
		q=log.get()
		if type(q)==list:
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
	a.join()
	for w in s:
		w.terminate()
	from time import sleep
	sleep(0.1)
	# Pool().map(cmp,[(log,w) for w in range(1)])
