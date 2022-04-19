from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

# for w in range(rand(100)):
# 	for e in range(rand(100)):
# 		print(rand(10))

n=rand(100)+1
print(n)
a=[]
for w in range(n):
	a.append(rand(100))
a.sort()
print(*a)
