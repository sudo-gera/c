from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

n=m=10**6
# n=rand(10**6)+1
# m=rand(10**6)+1
print(n,m)
for w in range(n):
	print(rand(99),end=' ')
print()
for w in range(m):
	y=rand(n)
	x=rand(y+1)
	print(x,y)
