from h import *
n,k=scan(),scan()
a=[scan() for w in range(n)]
s=0
for w in range(k):
	s+=a[s%n]
print(s)
