from json import *
ps=loads(open('/Users/gera/primes.txt').read())
def factor(q):
	oq=q
	f=[]
	for w in ps:
		if w*w>q:
			break
		while q%w==0:
			f.append(w)
			q//=w
	if q>1:
		if q<= ps[-1]**2:
			f.append(q)
		else:
			f.append(q)
			f.append(-1)			
	return f


def rad(q):
	from functools import reduce
	return reduce(lambda a,s:a*s,set(factor(q)),1)

p93=0
p10=0
while 1:
	if str(2**(p93*93+p10*10))[:1]=='9':
		a=2**(p93*93+p10*10)
		c=10**len(str(a))
		b=c-a
		from math import log
		if -1 not in factor(b):
			print(log(c,rad(a*b*c)))
		p93+=1
		p10+=1
	elif str(2**(p93*93+p10*10))[:1]<'3':
		p93+=1
	elif str(2**(p93*93+p10*10))[:1]>'3':
		p10+=1
	else:
		raise ValueError