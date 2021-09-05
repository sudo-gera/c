o=open
from os import *
open=o
from random import *
from time import *
from multiprocessing import *


def run2(a):
	n=len(a)
	s=[n-1-w for w in a]
	# ic(s)
	pm=[]
	zp=None
	for w in range(1,n+1):
		d=len(pm)
		for e in range(len(pm)):
			if pm[e]+e>=s[w-1]:
				d=e
				break
		pm=list(range(s[w-1],s[w-1]-d-1,-1))+[w-1 for w in pm[d:]]
		# print(pm)
		if zp==None:
			zp=s[0]
		for e in range(0,w):
			if pm[e]==0:
				return(len(a)-w)
	return(0)


def run3(a):
	n=len(a)
	s=tuple(enumerate(a))
	ss=set()
	gp=set()
	while s not in ss:
		ss.add(s)
		gp.add(s[0])
		s=s[1:len(s)-s[0][1]]+s[:1]+s[len(s)-s[0][1]:]
	return n-len(gp)



def run(p):
	p=str(int(time()*2**64))
	p=''
	while 1:
		dd=randint(2,5)
		open('stdin.txt'+p,'w').write(
				str(dd)+'\n'+
				' '.join([
					str(randint(1,dd-1)) for w in range(dd)
				])+'\n'
			)
		q=str(run3([int(w) for w in open('stdin.txt'+p).read().split()][1:]))
		a=str(run2([int(w) for w in open('stdin.txt'+p).read().split()][1:]))
		# q=popen('python3 test.py < stdin.txt'+p).read().strip()
		# a=popen('./a.out < stdin.txt'+p).read().strip()
		if q!=a:
			# print('differs ')
			print(open('stdin.txt'+p).read())
			# exit()

if __name__ == '__main__':
	run(0)