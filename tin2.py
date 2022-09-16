from h import *
n=scan()
a=[scan() for w in range(n)]
b=[scan() for w in range(n)]
c=[scan() for w in range(n)]
a.sort()
b.sort()
c.sort()
v=0
for w in range(n):
	for x in range(n):
		for y in range(n):
			if a[w]<b[x]<c[y]:
				v+=1
print(v)
