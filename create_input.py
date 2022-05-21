from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

def getstr():
	return ''.join([choice('snmrdfhg')+choice('aioue') for w in range(10)])

strs=[getstr() for w in range(20)]

n=rand(1,20)
k=rand(20)
print(n,k)
a=[rand(-6,6) for w in range(n)]
print(*a)
for w in range(k):
	q=rand(2)+1
	if q==1:
		print(q,rand(n),rand(-6,6))
	if q==2:
		e=rand(n)
		print(q,rand(e+1),e)
