task=3
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
	while 1:
		try:
			d=loads(s)
			break
		except:
			s+=stdin.read(1)
	print(d)