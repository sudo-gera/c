from numpy import *
from h import *

mod=3221225473
root=13
ro=2**30

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

# mod = 17
# root = 2
# ro = 8
assert bin(ro).count('1')==1

rp0=[0]*2**16
rp1=[0]*2**16

rp0[0]=1

for w in range(1,len(rp0)):
	rp0[w]=rp0[w-1]*root%mod

rp1[0]=1
rp1[1]=root*rp0[len(rp0)-1]

for w in range(2,len(rp1)):
	rp1[w]=rp1[w-1]*rp1[1]%mod

def roots(n,k=1):
	k%=n
	p=ro//n*k
	z=rp0[p%2**16]*rp1[p//2**16]%mod
	return z

bi=[]

def bitinv(t,l):
	while len(bi)<=t:
		r=len(bi)
		x=0
		for c in range(32):
			x*=2
			x+=r%2
			r//=2
		bi.append(x)
	return bi[t]>>(32-l)

def prep(a):
	l=-1
	o=len(a)
	while o:
		o//=2
		l+=1
	for w in range(len(a)):
		x=0
		r=w
		x=bitinv(r,l)
		if w<x:
			a[w],a[x]=a[x],a[w]

def fft(a,inv):
	b=0
	e=len(a)
	n=e-b
	assert bin(n).count('1')==1
	assert inv==-1 or max(a)**2*len(a)<mod
	perf()
	print()
	prep(a)
	perf()
	fftr(a,inv,b,e)
	perf()
	print()
	if inv==-1:
		for w in range(n):
			a[w]*=pow(n,-1,mod)
			a[w]%=mod
	return a

def fftr(a,inv,b,e):
	n=e-b
	h=n//2
	_n=n
	_b=b
	_e=e
	_h=h
	n=2
	while n<=_n:
		for b in range(_b,_e,n):
			e=b+n
			h=n//2
			for k in range(h):
				a0=a[b+k]
				a1=a[b+k+h]
				a[b+k]=(a0+roots(n,inv*k)*a1)%mod
				a[b+k+h]=(a0-roots(n,inv*k)*a1)%mod
		n*=2
	return a

# a=[scan() for w in range(8)]
# s=fft(a[:],1)
# print(*s,end=' \n')
# s=fft(a[:],-1)
# print(*s,end=' \n')
# assert fft(fft(a[:],1),-1)==a
# assert fft(fft(a[:],-1,),1)==a

def mul(q,e):
	l=max(len(q),len(e))
	dl=1
	while dl<l:
		dl*=2
	l=dl*2
	q+=[0]*(l-len(q))
	e+=[0]*(l-len(e))
	fft(q,1)
	fft(e,1)
	for w in range(len(q)):
		q[w]*=e[w]
		q[w]%=mod
	fft(q,-1)

for w in range(9):
	base=16
	q=scan(str)
	oq=int(q,base)
	q=q[::-1]
	q=[int(w,base) for w in q]
	e=scan(str)
	oe=int(e,base)
	e=e[::-1]
	e=[int(w,base) for w in e]
	mul(q,e)
	q=q[::-1]
	r=0
	for w in q:
		r*=base
		r+=w
	assert r==oq*oe
