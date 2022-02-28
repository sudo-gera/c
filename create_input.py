from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(999)
for w in range(n):
	q=rand(2)
	print(q,end=' ')
	if q:
		print(rand(10000),end=' ')
	print()
print(1000000000)
