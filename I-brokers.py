from h import *
n=scan()
a=[scan() for w in range(n)]
a.sort()
res=0
while len(a)>1:
	a=[a[0]+a[1]]+a[2:]
	res+=a[0]
	a.sort()
print(res)
