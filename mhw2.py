from functools import reduce
t=0
g=open('g.txt')
g=[w.split() for w in g]
g=[[w[0],reduce(lambda a,s:a[:-1]+[a[-1]+[int(s)]]if a and len(a[-1])==1 else a+[[s]],w[1:],[])] for w in g]
g=[[w[0],{'pos':dict(w[1]),'unt':8*60}] for w in g]
g=dict(g)
f=open('f.txt')
r=open('r.txt','w')
ct=8*60
for c in f:
	c=c.split()
	p=[g[w] for w in g if g[w]['unt']<=ct and c[1] in g[w]['pos']]
	if not p:
		p=min([g[w] for w in g if c[1] in g[w]['pos']],key=lambda a:a['unt'])
		ct=p['unt']
	else:
		p=p[0]
	t=ct+p['pos'][c[1]]
	print(c[0],' ',t//60,':',t%60,sep='',file=r)
	p['unt']=t
