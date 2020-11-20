task=6
if task==1:
	l=-1
	for w in range(1,3**10):
		s=[]
		w+=3**11
		while w:
			s.append(w%3)
			w//=3
		s=s[:10]
		c=[0,0,0]
		for w in range(3):
			if w in s:
				c[w]+=1
		while 0 in c:
			s.append((s[-10]+s[-9])%3)
			c[s[-1]]+=1
		l=max(l,len(s))
	print(l)
if task==2:
	for x in range(32):
		for k in range(32):
			z=x+19**(7+6)
			if (x+18*x*k**3+k)%32 == 13 and (z+18*z*k**3+k)%32 == 14:
				for y in 'уетехйе':
					y=ord(y)-ord('а')
					for x in range(32):
						if (x+18*x*k**3+k)%32 == y:
							x=chr(x+ord('а'))
							print(x,end='')
					print()
				print()
if task==3:
	def alic(q):
		return pow(q,15,32)
	y='хняжонзмюкйеэб'
	p,q=21,13
	y=[ord(w)-ord('а') for w in y]
	
	x=[float('inf') for w in range(43)]

	for w in range(14):
		x[2*w+15]=y[w]
	for w in range(7):
		x[40-2*w]=(x[41-2*w]-x[27-2*w])*29
	x[42]=x[28]+x[41]*p
	for w in range(6):
		x[26-2*w]=x[40-2*w]-x[39-2*w]*p
	for w in range(0,14):
		x[14-w]=x[28-w]-x[27-w]*q
	for w in x[1:15]:
		print(chr(w%32+ord('а')),end='')
	print()
if task==4:
	u=[-1]*400
	for d in range(2):
		for m in range(2):
			u[0]=(d*d-m*m)%2
			u[1]=(d*d*m)%2
			u[2]=(d+m)%2
			for w in range(3,400):
				u[w]=(u[w-3]+u[w-2]*u[w-1])%2
			y='жюшячмжощкрхю'
			y=[ord(w)-ord('а') for w in y]
			y=[[w//2**(4-e)%2 for e in range(5)] for w in y]
			for w in range(len(y)):
				for e in range(len(y[w])):
					y[w][e]+=u[w*5+e]
					y[w][e]%=2
			y=[[w[e]*2**(4-e) for e in range(5)] for w in y]
			y=[sum(w) for w in y]
			for w in y:
				print(chr(w%32+ord('а')),end='')
			print()
if task==5:
	part=3
	if part==1:
		for p in range(-10,10):
			if p**3+6*p**2-4*p-24==0:
				print(p)
	if part==2:
		for p in range(3):
			print((p**3+6*p**2-4*p-24)%3)
	if part==3:
		for p in [2,3,5,7,11,13,17,19,23,29]:
			for p1 in [2,3,5,7,11,13,17,19,23,29]:
				for p2 in [2,3,5,7,11,13,17,19,23,29]:
					for p3 in [2,3,5,7,11,13,17,19,23,29]:
						if p1<p2<p3 and p not in [p1,p2,p3]:
							if p**3+6*p**2-4*p-24==p1*p2*p3:
								print(p,p1,p2,p3)
if task==6:
	a=list(range(2**19))
	a=[[(w&(1<<e))>>e for e in range(19)] for w in a]
	a=[[w[e]&w[e+1]==0 for e in range(18)] for w in a]
	a=[w for w in a if all(w)]
	print(len(a))

