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

n=rand(1,20000)
print(n)
# q=rand(1,20000000000)
# print(n,q)
# for w in range(n):
	# c=choice(['+','-','=','?','??'])
	# if c in '+-':
	# 	print(c,rand(200),rand(n))
	# if c in '=?':
	# 	print(c,rand(n))
	# if c == '??':
	# 	print(c,rand(200))
	# print(rand(200),end=' ')
# print()
for w in range(n):
	print(choice('LR'),end='')
print()
