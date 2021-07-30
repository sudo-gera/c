from sys import setrecursionlimit
setrecursionlimit(1000000)
from functools import lru_cache
@lru_cache(maxsize=None)
def c(n,k):
	if k*2>n:
		return c(n,n-k)
	if k<0:
		return 0
	if k==0:
		return 1
	return c(n,k-1)*(n-k+1)//k
# колчиество графов на a вершинах, где ровно b вершин не связаны ни с чем
@lru_cache(maxsize=None)
def f(a,b):
	if b>a:
		return 0
	if a==b==0:
		return 1
	if a<0 or b<0:
		print('error',a,b)
		return 0
	if b:
		return c(a,b)*f(a-b,0)
	else:
		return sum([2**c(a,2)]+[-f(a,w) for w in range(1,a+1)])
def solve(n):
	return f(n,1)

from fractions import Fraction
@lru_cache(maxsize=None)
def fr(q):
	return Fraction(q).limit_denominator()

def froot(x,n):
	b=fr(0)
	e=fr(x+1)
	for w in range(64):
		c=(b+e)/2
		d=c**n
		if d<x:
			b=c
		if d>x:
			e=c
		if d==x:
			b=e=c
	return (b+e)/2

def fpow(a,s):
	s=fr(s)
	return froot(fr(a)**s.numerator,s.denominator)
