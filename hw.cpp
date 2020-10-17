#define up(a,q,w) (auto a=(q);a!=(w);a++)
#define dn(a,q,w) (auto a=(q);a!=(w);a--)
#include <bits/stdc++.h>
#define len(q,w) distance(q,w)
void shakersort(auto qb,auto qe):
	for up(w,qb,qe):
		for up(e,w,qe-1-w):
			if (*(e)>*(e+1)):
				swap(*(e),*(e+1);
		for dn(e,qe-1-w,w):
			if (*(e)<*(e-1)):
				swap(*(e),*(e-1));
void insertsort(auto qb,auto qe):
	e=[]
	for w in range(len(q)):
		insort(e,q[w])
	return e
void quicksort(auto qb,auto qe):
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
