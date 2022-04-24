from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

# n=rand(999)
# e=rand(n+1)
# x=rand(e+1)
# b=rand(x+1)
# print(n,b,e)
# for w in range(b):
# 	print([-1,1][rand(2)],end=' ')
# for w in range(b,x):
# 	print(-1,end=' ')
# for w in range(x,e):
# 	print(1,end=' ')
# for w in range(e,n):
# 	print([-1,1][rand(2)],end=' ')
# print()

n=rand(10**5)+1
s=rand(10**9)
print(n,s)
for w in range(n):
	b=rand(10**9)
	a=rand(b+1)
	c=rand(n)+1
	print(a,b,c)
