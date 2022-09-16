from h import *
n=scan()
a=[scan() for w in range(n)]
y=[
	[sum(a[e:w])*min(a[e:w]),e+1,w]
	for w in range(1,n+1)
		for e in range(w)
]
r,y=y,max(y)
print(y[0])
print(y[1],y[2])
