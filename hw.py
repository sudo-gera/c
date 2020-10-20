Tdef shakersort(q):
	q=q[:]
	for w in range(len(q)):
		for e in range(w,len(q)-1-w):
			if q[e]>q[e+1]:
				q[e],q[e+1]=q[e+1],q[e]
		for e in range(len(q)-1-w,w,-1):
			if q[e]<q[e-1]:
				q[e],q[e-1]=q[e-1],q[e]
	return q
def insertsort(q):
	from bisect import insort
	q=q[:]
	e=[]
	for w in range(len(q)):
		insort(e,q[w])
	return e
def quicksort(q):
	d=q[0]
	b=0
	e=len(q)-1
	while b<e:
		while q[b]<d:
			b+=1
		while q[e]>d:
			e-=1
		q[b],q[e]=q[e],q[b]
	return quicksort(q[:b])+quicksort(q[b:])

from random import *
def test(*a):
	a=[randint(1,100) for w in range(randint(1,100))]
	s=shakersort(a)
	i=insertsort(a)
	q=quicksort(a)
	t=sorted(a)
	if not(s==i==q==t):
		print(a)
from multiprocessing import *
Pool().map(test,range(1234567))
