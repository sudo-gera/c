from random import *
from fractions import Fraction
from sys import argv
run_num=int(argv[1]) if len(argv)>1 else 0
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

def getstr():
	return ''.join([choice('snmrdfhg')+choice('aioue') for w in range(10)])

maxlen=200+int(run_num**0.5)

strs=[getstr() for w in range(maxlen)]

n=rand(1,maxlen)
print(n)
a=[rand(maxlen) for w in range(n)]
print(*a)
f=rand(maxlen)
print(f)
for w in range(f):
	q=rand(7)+1
	if n==0:
		q=2
	else:
		r=rand(n)
		l=rand(r+1)
	print(q,end=' ')
	if q==1:
		print(l,r)
	if q==2:
		print(rand(maxlen),rand(n+1))
		n+=1
	if q==3:
		print(rand(n))
		n-=1
	if q==4:
		print(rand(maxlen),l,r)
	if q==5:
		print(rand(maxlen),l,r)
	if q==6:
		print(l,r)
	if q==7:
		print(l,r)