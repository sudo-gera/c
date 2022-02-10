from fractions import Fraction
from functools import total_ordering
from functools import reduce
from math import log
def find_root(q):
	w=2
	f=[]
	while w*w<=q:
		while q%w==0:
			f.append(w)
			q//=w
		w+=1
	if q!=1:
		f.append(q)
	d={}
	for w in f:
		d[w]=0
	for w in f:
		d[w]+=1
	e={}
	for w in d:
		e[w]=d[w]//2
		d[w]%=2
	d=sum([[w]*d[w] for w in d],[])
	e=sum([[w]*e[w] for w in e],[])
	g=lambda a,s:a*s
	return [reduce(g,d,1),reduce(g,e,1)]

@total_ordering
class Fraction_with_root:
	def __init__(s,r,a=0,b=0):
		if type(r)==Fraction_with_root:
			s.r=r.r
			s.a=r.a
			s.b=r.b
			return
		r=Fraction(r)
		a=Fraction(a)
		b=Fraction(b)
		assert r>0
		b/=r.denominator
		r=r.numerator*r.denominator
		r=find_root(r)
		b*=r[1]
		r=r[0]
		if r==1:
			a+=b
			b=0
		s.r=r
		s.a=a
		s.b=b
	def __repr__(s):
		return str(s.a)+'+'+str(s.b)+'*sqrt('+str(s.r)+')'
	def __eq__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		return s.a==a.a and s.b==a.b
	def __add__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		d=Fraction_with_root(s.r)
		d.a=s.a+a.a
		d.b=s.b+a.b
		return d
	def __neg__(s):
		d=Fraction_with_root(s.r)
		d.a=-s.a
		d.b=-s.b
		return d
	def __pos__(s):
		return s
	def __radd__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		return a+s
	def __sub__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		return s+-a
	def __rsub__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		return a+-s
	def __iadd__(s,a):
		return s+a
	def __isub__(s,a):
		return s-a
	def __mul__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		d=Fraction_with_root(s.r)
		d.a=s.a*a.a+s.r*s.b*a.b
		d.s=s.a*a.b+s.b*a.a
		return d
	def __rmul__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		return a*s
	def __imul__(s,a):
		return s*a
	def __truediv__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		return s*1/a
	def __rtruediv__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		if a==1:
			d= (s*Fraction_with_root(s.r,s.a,-s.b)).a
			s=Fraction_with_root(s.r,s.a,-s.b)
			s.a/=d
			s.b/=d
			return s
		else:
			return a*1/s
	def __idiv__(s,a):
		return s/a
	def is_not_negative(s):
		a=s.a
		b=s.b
		r=s.r
		if a==0:
			return b>=0
		if b==0:
			return a>=0
		if a>0:
			return not (-s).is_not_negative()
		if a<0 and b<0:
			return 0
		if a<0 and b>0:
			a=-a
			return b*b*r>=a*a
		assert 0
	def __ge__(s,a):
		if type(a)!=Fraction_with_root:
			a=Fraction_with_root(s.r,a)
		assert s.r==a.r
		return (s-a).is_not_negative()
	def __int__(s):
		d=int(s.a+s.b*s.r**0.5)
		while d<s:
			d+=1
		while d>s:
			d-=1
		return d
	def __float__(s):
		return s.a+s.b*s.r**0.5
	def __hash__(s):
		return hash((s.a,s.b,s.r))

def root(q):
	e=Fraction_with_root(q,0,1)
	if e.b==0:
		return e.a
	s=[]
	d={}
	while 1:
		if e in d:
			break
		d[e]=int(e)
		s.append(int(e))
		e=1/(e-int(e))
	end=e
	p=[]
	p.append(int(e))
	e=1/(e-int(e))
	while e!=end:
		p.append(int(e))
		e=1/(e-int(e))
	r=Fraction(1)
	for w in range(9999):
		for e in p[::-1]:
			r=e+1/r
	for e in s[::-1]:
		r=e+1/r
	return r

def check(q):
	q=(root(q)**2-q)/q
	return log(q.numerator)-log(q.denominator)

