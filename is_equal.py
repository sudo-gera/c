from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
if len(set(a))>1:
	exit(1)

# [l,*z]=[int(w) for w in a[0].split()]
# [n,*a,s]=[int(w) for w in p.split()]
# if l!=-1:
# 	assert len(z)==l and len(a)==n
# 	assert sum(z)==s
# 	assert all([w in a for w in z])
