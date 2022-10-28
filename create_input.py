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
def getstr(l=200):
	return ''.join([choice('snmrdfhg')+choice('aioue') for w in range(l)])[:l]
maxlen=200+int(run_num**0.5)
# strs=[getstr() for w in range(maxlen)]

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

# print(rand(),rand(),rand())

# a=open('test.txt','w')
# for w in range(rand(100)):
# 	a.write(rand(1000,10000))
# a.close()

# a=list(getstr(29000))
# s=list(getstr(29000))

# for w in range(100):
# 	d=list(getstr(10000))
# 	f=rand(len(a)-len(d)-1)
# 	a[f:f+len(d)]=d
# 	f=rand(len(a)-len(d)-1)
# 	s[f:f+len(d)]=d
# a=''.join(a)
# s=''.join(s)


# print(a)
# print(s)

# while 1:
# 	s=''.join([choice('1234567890?*?*') for w in range(rand(1,10))])
# 	a=list(s)
# 	while '?' in a:
# 		a[a.index('?')]=choice('1234567890')
# 	while '*' in a:
# 		a[a.index('*')]=''.join([choice('1234567890') for w in range(rand(2))])
# 	for w in range(rand(40)-2):
# 		a[choice(list(range(len(a))))]=choice('1234567890')
# 	if not a:
# 		a='1'
# 	if len(''.join(a))<700:
# 		print(''.join(a))
# 		print(s)
# 		break

n,m=rand(300),rand(30)
print(n,m)
for w in range(n):
	print(rand(9999),end=' ')
print()
