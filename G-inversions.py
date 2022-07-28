from h import *
n=scan()
a=[scan() for w in range(n)]
c=0
for w in range(n):
	for e in range(w):
		if a[w]<a[e]:
			c+=1
print(c)
