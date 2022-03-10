from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(4)
print(n)
a=[rand(2**30) for w in range(n)]
# a.sort()
# a=a[::-1]
print(*a)
