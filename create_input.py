from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(99)
for w in range(n):
	q=rand(5)
	print(q,end=' ')
	if q==1:
		print(rand()%256**3,end=' ')
	print()
