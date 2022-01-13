from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

n=rand(128)+1
print(n)
for w in range(rand(999)):
	m=rand(3)
	print(m+1)
	if m==0:
		print(rand(n),rand(n),rand(n),randint(-999,999))
	if m==1:
		x,y,z=rand(n),rand(n),rand(n)
		print(rand(x+1),rand(y+1),rand(z+1),x,y,z)
print(3)
