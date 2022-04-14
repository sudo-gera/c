from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

n=rand(1,300)
print(n)
for w in range(n):
	print(rand(9))
