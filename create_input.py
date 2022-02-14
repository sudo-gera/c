from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

print(0,2**8)
for w in range(1024):
	q=rand()%9
	if q==4:
		q+=1
	print(q,end=' ')
	if q in [0,1,2,3,6]:
		print(randint(-2**8,2**8),end=' ')
	print()
print(100000)
