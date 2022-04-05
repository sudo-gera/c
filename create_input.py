<<<<<<< HEAD
=======
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

ss='abocidure'

while 1:
	n=rand(9)+1
	a=''
	for w in range(n):
		a+=choice(ss)
	n=rand(9)+1
	s=''
	for w in range(n):
		s+=choice(list(ss)+[a]*4)
	a=s
	mc=-1
	ms=''
	for w in range(len(a)):
		for e in range(w):
			for c in range(1,len(a)):
				if a[w:w+c]==a[e:e+c]:
					if c>mc:
						mc=c
						ms=a[w:w+c]
	if ms:
		break
print(a)
>>>>>>> 63e0cbb4e069e3f02c93744f2a13b90ecdb0ea07
