from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(9999)
print(n)
a=[rand(9999) for w in range(n)]
a.sort()
print(*a)
