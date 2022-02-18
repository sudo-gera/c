from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

for w in range(rand(10)):
	q=rand(2)+1
	print(q)
	if q==1:
		print(rand(8*4),rand(2))
	else:
		print(rand(8*4))
print(0)
