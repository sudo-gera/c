from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(999)
print(n)
for w in range(n):
	print(rand(2**60)-2**59)
