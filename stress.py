def create_input_string():
	from random import randint
	n=randint(7,21)
	a=str(n)+'\n'
	for w in range(n):
		a+=str(randint(1,n))+' '
	return a

def how_to_run(filename):
	if filename.endswith('.cpp'):
		from time import time
		t='./'+str(time())+'.trash.trash'
		return [['g++','-std=c++17','-Wfatal-errors',filename,'-o',t],[t],['rm',t]]
	if filename.endswith('.c'):
		from time import time
		t='./'+str(time())+'.trash.trash'
		return [['cc','-Wfatal-errors',filename,'-o',t],[t],['rm',t]]
	if filename.endswith('.py'):
		return [['python3',filename]]
	if filename.endswith('.out'):
		return [[filename]]

def cmp(q=0):
	while 1:
		from sys import argv
		from subprocess import run,PIPE
		c=[how_to_run(w) for w in argv[1:]]
		p=create_input_string()
		c=[[run(e,stdout=PIPE,input=p.encode()) for e in w] for w in c]
		c=[[(e.stdout.decode() if hasattr(e,'stdout') and e.stdout!=None else '').strip()+\
			(e.stderr.decode() if hasattr(e,'stderr') and e.stderr!=None else '').strip()
			for e in w] for w in c]
		c=[''.join(w) for w in c]
		c=set(c)
		if len(c)!=1:
			print(p)

if __name__=='__main__':
	if type(create_input_string())!=str:
		raise\
			TypeError('create_input_string() function should return string, not '+type(create_input_string()).__name__)
	from sys import argv
	if len(argv)<3:
		raise\
			ValueError('need at least 2 files to compare, got '+str(len(argv)-1))
	from multiprocessing import Pool
	Pool().map(cmp,range(16))
