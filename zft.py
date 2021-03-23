task=2
if task==1:
	q=input().strip()
	q=q[1:-1].split(')(')
	q=[w.split('+') for w in q]
	q=[[[e.split('x^')[0],e.split('x^')[1].split('y^')[0],e.split('y^')[1]] for e in w] for w in q]
	q=[[[int(r) for r in e] for e in w] for w in q]
	a=[]
	for w in q[0]:
		for e in q[1]:
			a.append([w[0]*e[0],w[1]+e[1],w[2]+e[2]])
	a=[[w[0],f'x^{w[1]}y^{w[2]}'] for w in a]
	d=dict()
	for w in a:
		d[w[1]]=0
	for w in a:
		d[w[1]]+=w[0]
	a=[f'{d[w]}{w}' for w in d]
	a='+'.join(a)
	print(a)
if task==3:
	from sys import stdin
	from json import loads
	s=''
	l=0
	while 1:
		try:
			d=loads(s)[::-1]
			break
		except:
			s+=stdin.read(1)
			if len(s)==l:
				print('err')
				exit()
			l=len(s)
##########
	from functools import lru_cache
	@lru_cache
	def s(x,y):
		if x==0==y:
			return [d[x][y],None]
		if x==0:
			return [d[x][y]+s(x,y-1)[0],[x,y-1]]
		if y==0:
			return [d[x][y]+s(x-1,y)[0],[x-1,y]]
		a=min([s(x-1,y)+[[x-1,y]],s(x,y-1)+[[x,y-1]]])
		return [d[x][y]+a[0],a[2]]
	p=[len(d)-1,len(d[0])-1]
	ext=[]
	while p!=None:
		ext.append(p)
		p=s(*p)[1]
	ext=ext[::-1]
	for w in ext:
		print(w[1]+1,w[0]+1)
if task==2:
	from math import *
	def makesum(d1,d2):
		a,b,c,d=d1+d2
		j=1000
		a=max([[a*cos(w/j+b)+c*cos(w/j+d),2*pi-w/j] for w in range(int(j*pi*2))])
		return a
	from pprint import pprint
	from sys import stdin
	from json import loads
	from functools import reduce
	s=''
	l=0
	while 1:
		try:
			d=loads(s)
			break
		except:
			s+=stdin.read(1)
			if len(s)==l:
				print('err')
				exit()
			l=len(s)
	from math import atan2
	from math import pi
	d=[[w[0]*w[0]+w[1]*w[1],pi-atan2(w[1],w[0])*2] for w in d]
	f=reduce(makesum,d)
	print(f'y={1/tan(f[1]/2)}*x')















