from random import *
from fractions import Fraction
from sys import argv
run_num=int(argv[1]) if len(argv)>1 else 0
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)
def getstr():
	return ''.join([choice('snmrdfhg')+choice('aioue') for w in range(10)])
maxlen=200+int(run_num**0.5)
strs=[getstr() for w in range(maxlen)]

# def is_correst(a):
#     c=0
#     for w in a:
#         if w=='(':
#             c+=1
#         if w==')':
#             c-=1
#         if c<0:
#             return False
#     return c==0

# def create(n):
# 	if n<4:
# 		return '()'[:n]
# 	if rand(2):
# 		return '('+create(n-2)+')'
# 	else:
# 		t=randint(1,n//2-1)
# 		return create(t*2)+create(n-t*2)

# n=rand(1,4)*2
# q=rand(9)
# # q=1
# print(n,q)
# print(create(n))
# for w in range(q):
# 	print(rand(1,n+1),rand(1,n+1))

print(rand(),rand(),rand())