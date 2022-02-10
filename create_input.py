from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

for w in range(4):
	q=rand()%10
	print(q)
	if q==0:
		print(randint(-2**8,2**8))
	elif q==1:
		print(randint(-2**8,2**8))
	elif q==6:
		print(randint(-2**8,2**8))
		print(randint(-2**8,2**8))
	elif q==7:
		print(randint(-2**8,2**8))
	elif q==8:
		print(randint(-2**8,2**8))
print(10000000000000)
