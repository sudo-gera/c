from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
# if len(set(a))>1:
# 	exit(1)
# k=int(p.split()[-1])
# for f in a:
# 	f=int(f.strip())
# 	assert any([
# 		a[w:w+f].count('.')<=k
# 	for w in range(len(a))])
# 	f+=1
# 	assert f>len(a) or all([
# 		a[w:w+f].count('.')>k
# 	for w in range(len(a))])
p=p.split()
n=int(p[0])
p=[int(w) for w in p[1:]]
p.sort()
# print(p)
u=[p[w]==p[w-1] for w in range(1,len(p))].count(0)+1
for f in a:
	f=int(f)
	# print(u,f)
	assert u==f or u-1==f
