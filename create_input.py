from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

print(0,2**4)
for w in range(16):
	q=choice([0,1,2,3,4,5,7])
	# q=rand()%9
	print(q)
	if q in [0,1,2,3,6]:
		print(rand(2**8))
print(10000000000000)
