from h import *
n,m=scan([int,int])
a=scan([int]*n)
for w in range(m):
	q,x,c=scan([int,int,int])
	if q==1:
		a[x]=c
	if q==2:
		s=a[x:c+1]
		print(max([
			sum(s[w:e])
		for e in range(1,len(s)+1)
			for w in range(e)
		]))
