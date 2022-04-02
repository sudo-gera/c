from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

# n=rand(9)
# for w in range(n):
# 	q=choice([0]+[1,2]*9+[3,4])
# 	# q=rand(5)
# 	print(q,end=' ')
# 	if q==1:
# 		print(rand()%256**3,end=' ')
# 	print()
# print(99999)

n=100
print(n)
a=[]
while 1:
	for w in range(n):
		a+=[[randint(-10**3,10**3),randint(-10**3,10**3)]]
	if any([len(set(w))==1 for w in zip(*a)]):
		a=[]
	else:
		for w in a:
			print(*w)
		break
