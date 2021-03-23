from math import *
#from matplotlib.pyplot import plot
def makesum(a,b,c,d):
	j=1000
	a=max([[a*cos(w/j+b)+c*cos(w/j+d),2*pi-w/j] for w in range(int(j*pi*2))])
	return a

if 0:
	from random import *
	for w in range(1):
		[[a,b],[c,d]]=[[1, 0.0], [1, 3.141592653589793]]
		# a=randint(1,99)/100+1
		# b=randint(1,99)/100+1
		# c=randint(1,99)/100+1
		# d=randint(1,99)/100+1
		f=makesum(a,b,c,d)
		print(f)
		j=100
		s=all([a*cos(e/j+b)+c*cos(e/j+d)-f[0]*cos(e/j+f[1])<0.01 for e in range(int(j+pi+2))])
		if not s:
			print(a,b,c,d)


def df(q):
	sz=6
	q=str(q)
	if '.' in q:
		q=q[::-1]
		a=q.index('.')
		


	q=q[:-sz]+'.'+q[-sz:]
	while q[-1]=='0':
		q=q[:-1]
	while q[-1]=='.':
		q=q[:-1]
	while q[0]=='.':
		q='0'+q
	return q

print(df(0.02))