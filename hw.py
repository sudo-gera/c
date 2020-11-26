 from functools import lru_cache

lru_cache(maxsize=None)
def fib(n):
	if n==0:
		return 1
	if n==1:
		return 2
	return fib(n-1)+fib(n-2)

from math import factorial
def fac(n):
	return factorial(n+1)

def st3(n):
	return 3**n

def to(q,s):
	if q==0:
		return [0]
	n=0
	a=[]
	while s(n)<=q:
		n+=1
	while n>-1:
		d=0
		while s(n)<=q:
			q-=s(n)
			d+=1
		a+=[d]
		n-=1
	while a and a[0]==0:
		a=a[1:]
	return a

def tofib(q):
	return to(q,fib)

def tofac(q):
	return to(q,fac)

def to3(q):
	a=to(q,st3)
	for w in range(len(a)-1,-1,-1):
		while a[w]>1:
			a[w]-=3
			if len(a)==w+1:
				a.append(0)
			a[w+1]+=1
	return a
