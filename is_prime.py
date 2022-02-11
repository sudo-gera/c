p=pow
from math import *
pow=p
def is_visitor(a,n):
	if  gcd(a,n)!=1:
		return 0
	nn=n
	n-=1
	t=0
	while n%2==0:
		t+=1
		n//=2
	r=n
	n=nn
	assert n==1+r*2**t and r%2!=0
	s=t
	d=r
	print(s,d)
	ad=pow(a,d,n)
	if ad==1:
		return 1
	for w in range(s):
		ad=pow(ad,2,n)
		if ad==n-1:
			return 1
	return 0
	# ads=[ad]
	# for w in range(s):
	# 	ads.append(pow(ads[-1],2,n))
	# for w in ads[::-1]:
	# 	if w==n-1:
	# 		return 1
	# 	if w!=1:
	# 		return 0
	return 1

def is_prime_Miller(n):
	print(n)
	if n<2:
		return False
	for w in range(2, min(ceil(2*log(n)**2),n) ):
		if not is_visitor(w,n):
			print(w)
			return False
	return True
