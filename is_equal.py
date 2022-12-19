from sys import *
from json import *
a=loads(stdin.read())
# print(dumps(a))
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
if len(set(a))>1:
	exit(1)

# for a in a:
# 	a=[[int(e) for e in w.split()] for w in a.splitlines()]
# 	p=[[int(e) for e in w.split()] for w in p.splitlines()]
# 	assert len(a[0])==1
# 	assert len(a)==a[0][0]+1
# 	u=a[0][0]
# 	a=a[1:]
# 	import subprocess
# 	r=''
# 	for w in p+a:
# 		r+=' '.join([str(e) for e in w])+'\n'
# 	r=subprocess.run(['./comps.out'],encoding='utf-8',input=r,stdout=subprocess.PIPE)
# 	assert r.returncode==0
# 	r=eval(r.stdout)
# 	assert r[1]==[]
# 	r=''
# 	for w in p:
# 		r+=' '.join([str(e) for e in w])+'\n'
# 	r=subprocess.run(['./comps.out'],encoding='utf-8',input=r,stdout=subprocess.PIPE)
# 	assert r.returncode==0
# 	cm,r=eval(r.stdout)
# 	a=[[] for w in range(len(cm))]
# 	s=[[] for w in range(len(cm))]
# 	# print(r)
# 	for w in r:
# 		a[w[0]]+=[w[1]]	
# 		s[w[1]]+=[w[0]]
# 	# print(a,s)
# 	a=len([w for w in a if not w])
# 	s=len([w for w in s if not w])
# 	assert max(a,s)==u

# for a in a:
# 	assert all([len(w)==2 for w in a])
# 	assert all([q[-1]==w[0] for q,w in zip(a,a[1:])])
# 	if a:
# 		assert a[0][0]==a[-1][-1]
# 	n,s=p[0]
# 	p=p[1:]
# 	assert len(p)==n
# 	assert all([len(w)==n for w in p])
# 	# print(p)
# 	# print(a)
# 	for q in range(n):
# 		for w in range(n):
# 			# print(q,w)
# 			assert p[q][w]==1-([q,w] in a)
	






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