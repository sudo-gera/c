from math import *
from builtins import *
mmh=[]
def prime_checker(a,n,s,d):
	ad=pow(a,d,n)
	if ad==1:
		return 1
	for w in range(s):
		if ad==n-1:
			return 1
		ad=pow(ad,2,n)
	return 0

def is_prime_Miller(n):
	if n<2:
		return False
	nn=n
	n-=1
	t=0
	while n%2==0:
		t+=1
		n//=2
	r=n
	n=nn
	s=t
	d=r
	for a in range(2, min(ceil(2*log(n)**2),n) ):
		if not prime_checker(a,n,s,d):
			return False
	return True
