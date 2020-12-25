from math import *
from random import *
def rft(q,w):
	return random()*(w-q)+q
re=1.602176634*10**(-19)
res=[]
for w in range(80):
	t1=rft(0.5,2.2)
	t2=rft(4,6)
	u=choice([300,400,500])
	v1=0.0003/t1
	v2=0.0003/t2
	q=2.73*10**(-11)*(v1+v2)*sqrt(abs(v1-v2))/u
	n=q/re
	n=int(n+0.5)
	if n>3:
		continue
	e=q/n
	de=abs(e-re)
	res.append([de,t1,t2,e,u])
res.sort()
res=res[:15]
res=[[w[-1]]+w[:-1] for w in res]
res.sort()
for w in res:
	u,d,t1,t2,q=w
	w=[t1,t2]
	w=[str(int(e*100+100000000)) for e in w]
	w=[e[6:-2]+','+e[-2:] for e in w]
	w=[u,0.0003,w[0],0.0003,w[1]]
	w=[str(e).replace('.',',') for e in w]
	print(*w,sep='\t')