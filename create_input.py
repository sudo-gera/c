from random import *
from fractions import Fraction
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

# ss='abocidure'

# while 1:
# 	n=rand(9)+1
# 	a=''
# 	for w in range(n):
# 		a+=choice(ss)
# 	n=rand(9)+1
# 	s=''
# 	for w in range(n):
# 		s+=choice(list(ss)+[a]*4)
# 	a=s
# 	mc=-1
# 	ms=''
# 	for w in range(len(a)):
# 		for e in range(w):
# 			for c in range(1,len(a)):
# 				if a[w:w+c]==a[e:e+c]:
# 					if c>mc:
# 						mc=c
# 						ms=a[w:w+c]
# 	if ms:
# 		break
# print(a)

# while 1:
# 	q=rand(1000)
# 	p=rand(1000)
# 	c=0
# 	n=2
# 	f=2
# 	a=Fraction(p,q)
# 	while a:
# 		d=Fraction(0)
# 		while d/f<=a:
# 			d+=1
# 		d-=1
# 		c+=1
# 		a-=d/f
# 		n+=1
# 		f*=n
# 	if c<1000:
# 		print(p,q)
# 		break

# mod=17
# # mod=3221225473
# for w in range(8):
# 	print(rand(mod))
# print(rand(mod//4))
# print(rand(mod//4))

# from h import *
# n=rand(10)
# for w in range(n):
# 	print(to_radix(rand(999999),3))
# print(*to_radix(rand(),3).split('0')[:10])
# print('-'*100,*to_radix(int(argv[1])*999999999,3).split('0'),file=stderr)
# n=rand(16)
# print(n)
# for w in range(n):
# 	print(rand(9)-4)
# print(rand(2**2**10))
# print(rand(2**2**10))
n=rand(2**12)+1
for w in range(n):
	print(rand(2),end='')
print()
n=rand(2**12)+1
for w in range(n):
	print(rand(2),end='')
print()
