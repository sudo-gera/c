from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
if len(set(a))>1:
	exit(1)


# assert len({w.splitlines()[0] for w in a})==1
# a=''.join(['\n'.join(w.splitlines()[1:]) for w in a])
# a=[int(w) for w in a.split()]
# p=[int(w) for w in p.split()][2:]
# p=set(zip(p[::2],p[1::2]))
# for w in zip(a,a[1:]+a[:1]):
# 	assert w in p



# f=[]
# for q in a:
# 	[l,*z]=[int(w) for w in q.split()]
# 	[n,*m]=[int(w) for w in p.split()]
# 	assert len(z)==l
# 	o=[m[w] for w in z]	
# 	assert sorted(o)==o
# 	f.append(l)
# assert len(set(f))==1