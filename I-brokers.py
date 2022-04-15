from h import *
n=scan()
a=[scan() for w in range(n)]
ca=[]
def get(b,e):
	while len(ca)<=b:
		ca.append([])
	while len(ca[b])<=e:
		ca[b].append([])
	if ca[b][e]==[]:
		assert b!=e
		if e-b==1:
			return [0,a[b]]
		l=[]
		for w in range((b+e+1)//2,e):
			c=w
			z=get(b,c)
			x=get(c,e)
			c=z[0]+x[0]+z[1]+x[1]
			v=z[1]+x[1]
			l.append([c,v])
		r=min(l)
		ca[b][e]=r
	return ca[b][e]
a.sort()
x=get(0,len(a))[0]
print(x)
