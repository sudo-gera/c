import fractions
import bisect
import numbers
import functools
import math
# from fractions import Fraction
# from functools import total_ordering
# from functools import reduce
# from functools import cache, lru_cache
try:
	cache = functools.cache
except:
	cache=functools.lru_cache(maxsize=None)
from numbers import Rational
# from time import time
# from bisect import *
@cache
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
	return [functools.reduce(g,d,1),functools.reduce(g,e,1)]

class froot(Rational):
	def __init__(s,r,a=None,b=None):
		if type(r)==froot:
			s.r=r.r
			s._a=r.a
			s._b=r.b
			return
		if a==None and b==None:
			a,b=0,1
		elif b==None:
			b=0
		r=fractions.Fraction(r)
		a=fractions.Fraction(a)
		b=fractions.Fraction(b)
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
		s._a=a
		s._b=b
	@property
	def a(s):
		return s._a
	@property
	def b(s):
		return s._b
	def __repr__(s):
		return '('+str(s.a)+'+'+str(s.b)+'*froot('+str(s.r)+')'+')'
	def __eq__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		return s.a==a.a and s.b==a.b
	def __add__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		d=froot(s.r,s.a+a.a,s.b+a.b)
		return d
	def __neg__(s):
		d=froot(s.r,-s.a,-s.b)
		return d
	def __pos__(s):
		return s
	def __radd__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		return a+s
	def __sub__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		return s+-a
	def __rsub__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		return a+-s
	def __iadd__(s,a):
		return s+a
	def __isub__(s,a):
		return s-a
	def __mul__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		d=froot(s.r,s.a*a.a+s.r*s.b*a.b,s.a*a.b+s.b*a.a)
		return d
	def __rmul__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		return a*s
	def __imul__(s,a):
		return s*a
	def invert(s):
		assert s!=0
		pr=froot(s.r,s.a,-s.b)
		d=(s*pr).a
		s=pr
		s=froot(s.r,s.a/d,s.b/d)
		return s
	def __truediv__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		return s*a.invert()
	def __rtruediv__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		return a/s
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
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		return (s-a).is_not_negative()
	def __le__(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		assert s.r==a.r
		return (a-s).is_not_negative()
	def __lt__(s,a):
		return not s>=a
	def __gt__(s,a):
		return not s<=a
	def __float__(s):
		return s.a+s.b*s.r**0.5
	def __hash__(s):
		return hash((s.a,s.b,s.r))
	def __pow__(s,o):
		if type(o)==int:
			r=s-s+1
			while o:
				if o&1:
					r*=s
				o>>=1
				s*=s
			return r
	def __abs__(s):
		if s<0:
			return -s
		return s
	def near_int(s):
		return int(s.a)+floor_root(s.b**2*s.r)
	def __ceil__(s):
		d=s.near_int()
		while d>s:
			d-=1
		while d<s:
			d+=1
		return d
	def __floor__(s):
		d=s.near_int()
		while d<s:
			d+=1
		while d>s:
			d-=1
		return d
	def __int__(s):
		return int(fractions.Fraction(math.ceil(s)+math.floor(s))/2)
	@cache
	def divmod(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		z=math.floor(s/a)
		return [z,s-z*a]
	def __floordiv__(s,o):
		return s.divmod(o)[0]
		# return floor(s/o)
	def __rfloordiv__(s,o):
		if type(o)!=froot:
			o=froot(s.r,o)
		return o.divmod(s)[0]
		# return floor(o/s)
	def __mod__(s,o):
		return s.divmod(o)[1]
		# return s-s//o*o
	def __rmod__(s,o):
		if type(o)!=froot:
			o=froot(s.r,o)
		return o.divmod(s)[1]
		# return o-o//s*s
	def __imod__(s,o):
		return s%o
	def __ifloordiv__(s,o):
		return s//o
	def __round__(s,d=0):
		return round(fractions.Fraction(s))
	def __rpow__(s,o):
		return o**float(s)
	def __trunc__(s):
		return int(s)
	def as_fraction(s):
		return s.a+s.b*fractional_root(s.r)
	@property
	def numerator(s):
		return s.as_fraction().numerator
	@property
	def denominator(s):
		return s.as_fraction().denominator

# def check(q,f):
# 	from time import perf_counter
# 	a=perf_counter()
# 	fq=f(q)
# 	a=perf_counter()-a
# 	fq=Fraction(fq)
# 	q=(fq**2-q)/q
# 	q=abs(q)
# 	if q==0:
# 		f=float('-inf')
# 	else:
# 		f=log(q.numerator)-log(q.denominator)
# 	print(f)
# 	if f<-10000:
# 		return a
# 	else:
# 		raise ValueError


def continued_root(q):
	if type(q)==fractions.Fraction:
		return math.root(q.numerator)/math.root(q.denominator)
	if type(q)==froot:
		return q.as_fraction()
	if type(q)!=int:
		return math.root(fractions.Fraction(q))
	if q==0:
		return fractions.Fraction(0)
	e=froot(q)
	# if e.b==0:
	# 	return e.a

	a=[]
	ie=math.floor(e)
	a.append(ie)
	e=1/(e-ie)
	ie=math.floor(e)
	a.append(ie)
	e=1/(e-ie)

	p_2=a[0]
	q_2=1
	p_1=a[0]*a[1]+1
	q_1=a[1]

	s=[]
	index=-1
	d=set()
	for w in range(2,9999):
		if index == -1:
			ie=math.floor(e)
			a=ie
			if e in d:
				s=s[s.index(a):]
				index=1%len(s)
			else:
				d.add(e)
				s.append(a)
			e=1/(e-ie)
		else:
			a=s[index]
			index=(index+1)%len(s)


		p=a*p_1+p_2
		q=a*q_1+q_2
		p_1,p_2=p,p_1
		q_1,q_2=q,q_1
	return fractions.Fraction(p)/fractions.Fraction(q)

def floor_root(q):
	q=int(q)
	r=0
	p=q.bit_length()+2
	p+=p%2
	p=1<<p
	while p:
		u=r+p
		if q >= u :
			q-=u
			r+=p
			r+=p
		r>>=1
		p>>=2
	return r

def ceil_root(q):
	s=floor_root(q)
	if s*s<q:
		return s+1
	return s

def fractional_root(q):
	if type(q)==fractions.Fraction:
		return fractional_root(q.numerator)/fractional_root(q.denominator)
	if type(q)==froot:
		return q.as_fraction()
	if type(q)!=int:
		return fractional_root(fractions.Fraction(q))
	p=2**15
	# p=2**p
	return fractions.Fraction(floor_root(q<<p<<p),1<<p)









