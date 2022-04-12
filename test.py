from numpy import *
from h import *

# q=scan()
# oq=q
# l=[]
# while q:
# 	l.append(q%10)
# 	q//=10
# q=l
# q+=[0]*(8-len(q))
# e=scan()
# oe=e
# l=[]
# while e:
# 	l.append(e%10)
# 	e//=10
# e=l
# e+=[0]*(8-len(e))
# mod=3221225473
# root=5**3
# root=pow(5,(3*2**27),mod)
mod = 17
root = 2
_p=root
_c=1
while _p!=1:
	_p*=root
	_p%=mod
	_c+=1
ro=_c
assert bin(ro).count('1')==1

def roots(n,k=1):
	k%=n
	p=root
	while n<ro:
		n*=2
		p*=p
	assert n==ro
	return pow(p,k,mod)

def fft(a):
	if len(a)==1:
		return a
	n=len(a)
	assert bin(n).count('1')==1
	a0=a[::2]
	a1=a[1::2]
	y0=fft(a0)
	y1=fft(a1)
	y=[]
	for k in range(len(a)//2):
		y.append(y0[k]+roots(n,k)*y1[k])
	for k in range(len(a)//2):
		y.append(y0[k]-roots(n,k)*y1[k])
	y=[w%mod for w in y]
	return y

def ifft(a):
	if len(a)==1:
		return a
	n=len(a)
	assert bin(n).count('1')==1
	a0=a[::2]
	a1=a[1::2]
	y0=fft(a0)
	y1=fft(a1)
	y=[]
	for k in range(len(a)//2):
		y.append(y0[k]+roots(n,-k)*y1[k])
	for k in range(len(a)//2):
		y.append(y0[k]-roots(n,-k)*y1[k])
	y=[w%mod for w in y]
	return y

a=[scan() for w in range(8)]
a=fft(a)
for w in a:
	print(w)
