from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

<<<<<<< HEAD
print(0,2**8)
for w in range(128):
	q=rand()%10
	print(q)
	if q in [0,1,6,7,8]:
		print(rand(2**16))
	if q in [6]:
		print(rand(2**16))
print(10000000000000)
=======
# for w in range(rand(10)):
# 	q=rand(2)+1
# 	print(q)
# 	if q==1:
# 		print(rand(8*4),rand(2))
# 	else:
# 		print(rand(8*4))
# print(0)
# print(rand(92299339))


# n=randint(1,9)
# q=randint(1,10**n-1)
# print(q,n)

# m=randint(1,999)
# q=randint(1,m)
# print(m,q)
q=''.join([choice('qwertyuiopasdfghjklzxcvbnm') for w in range(rand(9)+1)])
print(q)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
