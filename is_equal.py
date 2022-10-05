from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
if len(set(a))>1:
	exit(1)

# f=[]
# for q in a:
# 	[l,*z]=[int(w) for w in q.split()]
# 	[n,*m]=[int(w) for w in p.split()]
# 	assert len(z)==l
# 	o=[m[w] for w in z]	
# 	assert sorted(o)==o
# 	f.append(l)
# assert len(set(f))==1