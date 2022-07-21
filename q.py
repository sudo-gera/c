from h import *
n=scan()
a=[scan() for w in range(n)]
print(max([
	sum(a[e:w])*min(a[e:w])
	for w in range(1,n+1)
		for e in range(w)
]))