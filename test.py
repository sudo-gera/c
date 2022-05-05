from h import *

base=2

def mul(a,ba,ea,d,bd,ed,b,bb):
	la=ea-ba
	ld=ed-bd
	assert la+ld<=len(b)-bb
	if ba==ea or bd==ed:
		return
	if ed-bd==1:
		for w in range(la):
			b[bb+w]=d[bd]*a[ba+w]
		return
	if ea-ba==1:
		for w in range(0,ld):
			b[bb+w]=d[bd+w]*a[ba]
		return
	assert bin(la).count('1')==1 and bin(ld).count('1')==1
	assert la==ld
	l=la
	h=l//2
	assert h*2==l
	z=[a[ba+w]+a[ba+w+h] for w in range(h)]
	x=[d[bd+w]+d[bd+w+h] for w in range(h)]
	c=[0]*l
	v=[0]*l
	n=[0]*l
	mul(a,ba,ba+h,d,bd,bd+h,c,0)
	mul(a,ba+h,ea,d,bd+h,ed,v,0)
	mul(z,0,h,x,0,h,n,0)
	for w in range(l):
		b[bb+w]+=c[w]
	for w in range(l):
		b[bb+w+l]+=v[w]
	for w in range(l):
		b[bb+w+h]+=n[w]
	for w in range(l):
		b[bb+w+h]-=c[w]
	for w in range(l):
		b[bb+w+h]-=v[w]


for w in range(1):
	perf()
	# a=[rand(4) for w in range(8)]
	# s=[rand(4) for w in range(8)]
	a=[rand(100) for w in range(2048)]
	s=[rand(100) for w in range(2048)]
	_a=a
	_s=s
	d=[0]*(len(a)+len(s))
	perf()
	mul(a,0,len(a),s,0,len(s),d,0)
	perf()
	_d=d
	a=a[::-1]
	s=s[::-1]
	d=d[::-1]
	r=0
	for w in a:
		r*=10000
		r+=w
	a=r
	r=0
	for w in s:
		r*=10000
		r+=w
	s=r
	r=0
	for w in d:
		r*=10000
		r+=w
	d=r
	perf()
	if a*s!=d:
		print(_a,_s,_d)
