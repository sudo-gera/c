from json import *
from os import *
from sys import *
from subprocess import *
from multiprocessing import Pool,Queue,Process
from os import system
from os.path import exists
from queue import Queue as bq
from subprocess import run,PIPE,Popen,TimeoutExpired
from sys import argv,executable
from time import sleep,time, asctime
from traceback import format_exc
import signal
from sys import stderr
from ast import parse
from builtins import *
from py_compile import compile,PyCompileError

compiler='g++'

flags=['-O2']

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
			if run(['g++','-Ofast','-std=c++20','-Wfatal-errors',filename,'-o',compiled_file]).returncode:
				exit()
		if filename.endswith('.c'):
			if run(['g++','-Ofast','-std=c++20','-Wfatal-errors',filename,'-o',compiled_file]).returncode:
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



test_creator='gen_test.py'

to_run='task.cpp'

def run_with_time(a):
    s=run(['time','-p']+a,stderr=PIPE)
    t=s.stderr
    t=t.splitlines()
    t = [w for w in t if w]
    t=t[-3]
    if b'real' in t:
        t=t.split(b'real',1)[1]
    t=t.strip()
    return t.decode(errors='replace')

res=[]
start_time=str(time()*2**64)
for w in range(20):
    run(how_to_run(test_creator,start_time))
    n=int(open('test.txt','r').read().split()[0])
    t=run_with_time(how_to_run(to_run,start_time))
    res.append([n,t])

print('result:')
for w in res:
    print(*w)