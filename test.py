from h import *
n,b,e=scan(int,int,int)
a=[scan(int) for w in range(n)]
a=a[b:e]
x=([w>0 for w in a]+[1]).index(1)
z=[(w>0) ^ (q<x) for q,w in enumerate(a)]
assert(all(z))
print(x+b)
