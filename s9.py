n,s=[int(w) for w in input().split()]
a=[]
b=[]
c=[]
for w in range(n):
	a.append(0)
	b.append(0)
	c.append(0)
	a[-1],b[-1],c[-1]=[int(w) for w in input().split()]
def get(_c):
	# print(_c,end=' ')
	z=[
			a[w]
		if c[w]>=_c else
			b[w]
	for w in range(n)]
	# print(z,end=' ')
	z.sort()
	z=z[:_c]
	if sum(z)>s:
		r=1
	else:
		r=0
	# print(r)
	return r

class f:
	def __getitem__(s,n):
		return get(n)
	def __len__(s):
		return n+1

from bisect import *

z=bisect_left(f(),1)
print(z-1)

# [f()[w] for w in range(20)]

