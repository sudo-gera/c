from numpy import *
from h import *

# mod=3221225473
# root=13
# ro=2**30

# for m in count(2):
# m=mod
# for r in range(mod):
# 	l=[[3*2**w,2**w] for w in range(30)]
# 	l=sum(l,[])
# 	l=[pow(r,w,m) for w in l]
# 	l=[w!=1 for w in l]
# 	l.append(pow(r,2**30,m)!=1)
# 	# l.append(pow(r,2**30,m)==1)
# 	if all(l):
# 		print(r,m)


# mod=3221225473
# root=5**3
# ro=2**30

mod = 17
root = 2
ro = 8
assert bin(ro).count('1')==1


def roots(n,k=1):
	k%=n
	p=root
	while n<ro:
		n*=2
		p*=p
		p%=mod
	assert n==ro
	return pow(p,k,mod)

def prep(a):
	l=-1
	o=len(a)
	while o:
		o//=2
		l+=1
	for w in range(len(a)):
		x=0
		r=w
		for c in range(l):
			x*=2
			x+=r%2
			r//=2
		if w<x:
			a[w],a[x]=a[x],a[w]


def fft(a,inv,b=0,e=None,o=1):
	if e==None:
		e=len(a)
	n=e-b
	if n==1:
		return a
	assert bin(n).count('1')==1
	if o==1:
		prep(a)
	fft(a,inv,b,b+n//2,o+1)
	fft(a,inv,b+n//2,e,o+1)
	for k in range(n//2):
		a0=a[b+k]
		a1=a[b+k+n//2]
		a[b+k]=a0+roots(n,inv*k)*a1
		a[b+k+n//2]=a0-roots(n,inv*k)*a1
	if inv==-1:
		for w in range(n):
			a[b+w]=a[b+w]*pow(2,-1,mod)%mod
	else:
		for w in range(n):
			a[b+w]=a[b+w]%mod
	return a

# a=[scan() for w in range(8)]
# s=fft(a[:],1)
# print(*s,end=' \n')
# s=fft(a[:],-1)
# print(*s,end=' \n')
# assert fft(fft(a[:],1),-1)==a
# assert fft(fft(a[:],-1,),1)==a


q=scan()
oq=q
l=[]
while q:
	l.append(q%10)
	q//=10
q=l
e=scan()
oe=e
l=[]
while e:
	l.append(e%10)
	e//=10
e=l
q+=[0]*(8-len(q))
e+=[0]*(8-len(e))
print(q,e,oq,oe)
fft(q,1)
fft(e,1)
print(q,e)
for w in range(len(q)):
	q[w]*=e[w]
print(q)
fft(q,-1)
print(q)
q=q[::-1]
r=0
for w in q:
	r*=10
	r+=w
print(r,oq*oe)
assert r==oq*oe
