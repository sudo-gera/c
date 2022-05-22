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

n=rand(1,128)
print(n)
for w in range(rand(60000)):
	q=rand(2)+1
	print(q)
	if q==1:
		print(rand(n),rand(n),rand(n),rand(-60,61))
	if q==2:
		w,e,r=rand(n),rand(n),rand(n)
		print(rand(w+1),rand(e+1),rand(r+1),w,e,r)
print(3)
