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

maxlen=100+int(run_num**0.5)

strs=[getstr() for w in range(maxlen)]

n=rand(1,maxlen)
print(n)
a=[rand(maxlen) for w in range(n)]
print(*a)
