from sys import argv
from subprocess import *
from re import *
from threading import Thread
if len(argv)<2:
	print('\x1b[101;30mERROR\x1b[0m\x1b[94m run \n\x1b[92mpython3 trace.py \x1b[95mfilename.cpp\x1b[0m')
	exit()
a=open(argv[1]).read()
a=split(r'}\s;',a)
a='}\0'.join(a)
# start=b'\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x1f\x1e\x1d\x1c\x1b\x1a\x19\x18\x17\x16\x15\x14\x13\x12\x11\x10\x0f\x0e\x0d\x0c\x0b\x0a\x09\x08\x07\x06\x05\x04\x03\x02\x01'
start=b'\x02\x03'
s=''
b=''
while a:
	if a[0] in ')' or a[0] in '\'"' and b and b[-1]==a[0]:
		b=b[:-1]
		s+=a[0]
		a=a[1:]
	elif a[0] in '(\'"':
		b+=a[0]
		s+=a[0]
		a=a[1:]
	elif a[0]==';' and not b:
		s+=';printf("'+repr(start.decode())[1:-1]+'%i\\x01",__LINE__);'
		a=a[1:]
	else:
		s+=a[0]
		a=a[1:]
a=s
# a=a.replace(';',';printf("'+repr(start.decode())[1:-1]+'%i\\x01",__LINE__);')
a=a.replace('}\0','};')
a='#include<stdio.h>\n'+a
open('trace.py.cpp','w').write(a)
if run('g++ -std=c++17 trace.py.cpp'.split()).returncode:
	exit()
a=Popen(['./a.out'],stdout=PIPE)
from queue import Queue
lines=Queue()
def getstdout():
	from sys import stdout
	b=b''
	while (q:=a.stdout.read(1)) or a.poll()==None:
		b+=q
		if b.startswith(start):
			if b'\x01' in b[len(start):]:
				b=b[len(start):]
				b=b.split(b'\x01')
				lines.put(int(b[0]))
				stdout.buffer.write(b[1])
				b=b''
		else:
			if start.startswith(b):
				pass
			else:
				stdout.buffer.write(b)
				b=b''
		stdout.flush()
	lines.put('exit')
t=Thread(target=getstdout)
t.start()
ll=[]
working=1
while working:
	q=lines.get()
	if q!='exit':
		ll.append(q)
	else:
		working=0
if ll:
	print('\x1b['+str(91 if a.returncode else 92)+'mexecution stopped at line',ll[-1]-1,'\x1b[0m')
else:
	print('\x1b['+str(91 if a.returncode else 92)+'mexecution didn`t start \x1b[0m')