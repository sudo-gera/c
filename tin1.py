from h import *
al=input()
n=scan()
a=[scan(str) for w in range(n)]
def cmp(z,x):
	z=[al.index(w) for w in z]
	x=[al.index(w) for w in x]
	if z<x:
		return -1
	if z>x:
		return 1
	return 0
a.sort(key=cmp_to_key(cmp))
for w in a:
	print(w)
