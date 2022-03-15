from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(99)
print(n)
a=[rand(2**30) for w in range(n)]
print(*a)
