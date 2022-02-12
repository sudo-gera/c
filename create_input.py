from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

print(0,2**8)
for w in range(4):
	q=rand()%10
	print(q)
	if q in [0,1,6,7,8]:
		print(rand(2**23))
	if q in [6]:
		print(rand(2**23))
print(10000000000000)
