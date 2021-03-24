def makesum():
	j=1000
	a=max([[ff(w/j),2*pi-w/j] for w in range(int(j*pi*2))])
	return a

def lprint(q):
	print(q)
	return q

def makesum2():
	j=16
	k=4
	aa=([[ff(w/j),w/j] for w in range(int(j*pi*4))])
	s=max([[sum([t[0] for t in aa[w:w+k]]),w] for w in range(len(aa))])[1]
	aa=aa[s:s+k]
	fi,st=aa[0][1],aa[-1][1]
	l=64
	for t in range(l):
		cl=(st+st+fi)/3
		cr=(st+fi+fi)/3
		if ff(cl) < ff(cr):
			st=cl
		if ff(cl) > ff(cr):
			fi=cr
		if ff(cl) ==ff(cr):
			st=cl
			fi=cr
	res=(fi+st)/2
	res=res%(pi*2)
	return [ff(cl),2*pi-res]
								


from math import *
from random import *
for w in range(10000):
	a=randint(1,99)/100+1
	b=randint(1,99)/100+1
	c=randint(1,99)/100+1
	d=randint(1,99)/100+1
	ff=lambda x:a*cos(x+b)+c*cos(x+d)
	e,f=makesum2()
	j=100
#	print([a*cos(g/j+b)+c*cos(g/j+d)-e*cos(g/j+f) for g in range(int(j*pi*2))])
	if not all([0.000000001>ff(g/j)-e*cos(g/j+f) for g in range(int(j*pi*2))]):
		print(a,b,c,d)
