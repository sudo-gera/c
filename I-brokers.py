from h import *
n=scan()
a=[scan() for w in range(n)]
def get(a,b,e):
	assert b!=e
	if e-b==1:
		return [0,a[b]]
	l=[]
	for w in range(b+1,e):
		c=w
		z=get(a,b,c)
		x=get(a,c,e)
		c=z[0]+x[0]+z[1]+x[1]
		v=z[1]+x[1]
		l.append([c,v])
	return min(l)
print(min([get(w,0,len(w))[0] for w in permutations(a)]))
