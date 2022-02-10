from fractions import Fraction
from functools import total_ordering
from functools import reduce
from functools import cache
from math import *
from numbers import Rational
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
	return [reduce(g,d,1),reduce(g,e,1)]

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
		s._a=a
		s._b=b
	@property
	def a(s):
		return s._a
	@property
	def b(s):
		return s._b
	def __repr__(s):
		return str(s.a)+'+'+str(s.b)+'*froot('+str(s.r)+')'
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
		return int(s.a)+floor_root(s.b**2+s.r)
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
		return int(Fraction(ceil(s)+floor(s))/2)
	@cache
	def divmod(s,a):
		if type(a)!=froot:
			a=froot(s.r,a)
		z=floor(s/a)
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
		return round(Fraction(s))
	def __rpow__(s,o):
		return o**float(s)
	def __trunc__(s):
		return int(s)
	def as_fraction(s):
		return s.a+s.b*fraction_root(s.r)
	@property
	def numerator(s):
		return s.as_fraction().numerator
	@property
	def denominator(s):
		return s.as_fraction().denominator

def check(q,f):
	from time import perf_counter
	a=perf_counter()
	fq=f(q)
	a=perf_counter()-a
	fq=Fraction(fq)
	q=(fq**2-q)/q
	q=abs(q)
	if q==0:
		f=float('-inf')
	else:
		f=log(q.numerator)-log(q.denominator)
	if f<-10000:
		return a
	else:
		raise ValueError


def root(q):
	if type(q)==Fraction:
		return root(q.numerator)/root(q.denominator)
	if type(q)==froot:
		return q.as_fraction()
	if type(q)!=int:
		return root(Fraction(q))
	if q==0:
		return Fraction(0)
	e=froot(q,0,1)
	if e.b==0:
		return e.a
	s=[]
	d=set()
	while 1:
		if e in d:
			break
		ie=floor(e)
		d.add(e)
		s.append(ie)
		e=1/(e-ie)
	end=e
	p=[]
	p.append(floor(e))
	e=1/(e-floor(e))
	while e!=end:
		ie=floor(e)
		p.append(ie)
		e=1/(e-ie)
	l=p
	s+=p+p
	p_2=s[0]
	q_2=1
	p_1=s[0]*s[1]+1
	q_1=s[1]
	for w in range(2,9999):
		if w<len(s):
			a=s[w]
		else:
			a=l[(w-len(s))%len(l)]
		p=a*p_1+p_2
		q=a*q_1+q_2
		p_1,p_2=p,p_1
		q_1,q_2=q,q_1
	return Fraction(p,q)

# def fast_root(q):
# 	if type(q)==Fraction:
# 		return root(q.numerator)/root(q.denominator)
# 	if type(q)==froot:
# 		return q.as_fraction()
# 	if type(q)!=int:
# 		return root(Fraction(q))
# 	if q==0:
# 		return Fraction(0)
# 	e=froot(q)
# 	if e.b==0:
# 		return e.a
# 	# s=[]
# 	# d=set()
# 	# while 1:
# 	# 	if e in d:
# 	# 		break
# 	# 	ie=floor(e)
# 	# 	d.add(e)
# 	# 	s.append(ie)
# 	# 	e=1/(e-ie)
# 	# end=e
# 	# p=[]
# 	# p.append(floor(e))
# 	# e=1/(e-floor(e))
# 	# while e!=end:
# 	# 	ie=floor(e)
# 	# 	p.append(ie)
# 	# 	e=1/(e-ie)
# 	# l=p
# 	# s+=p+p
# 	n=[e,1]
# 	def get_n(w):
# 		if len(n)>w:
# 			return n[w]
# 		for e in range(len(n),w):
# 			get_n(e)
# 		n.append(n[w-2] % n[w-1])
# 		return n[w]
# 	def get_a(w):
# 		# print(w)
# 		# if w<len(s):
# 		# 	a=s[w]
# 		# else:
# 		# 	a=l[(w-len(s))%len(l)]
# 		# return a
# 		return get_n(w)//get_n(w+1)

# 	p_2=get_a(0)
# 	q_2=1
# 	p_1=get_a(0)*get_a(1)+1
# 	q_1=get_a(1)
# 	for w in range(2,99):
# 		a=get_a(w)
# 		p=a*p_1+p_2
# 		q=a*q_1+q_2
# 		p_1,p_2=p,p_1
# 		q_1,q_2=q,q_1
# 	return Fraction(p,q)

# def fast_root1(q):
# 	if type(q)==Fraction:
# 		return root(q.numerator)/root(q.denominator)
# 	if type(q)==froot:
# 		return q.as_fraction()
# 	if type(q)!=int:
# 		return root(Fraction(q))
# 	if q==0:
# 		return Fraction(0)
# 	e=froot(q)
# 	if e.b==0:
# 		return e.a
# 	def get_as():
# 		nonlocal e
# 		# s=[]
# 		# d=set()
# 		while 1:
# 			# if e in d:
# 			# 	break
# 			ie=floor(e)
# 			# d.add(e)
# 			# s.append(ie)
# 			yield ie
# 			e=1/(e-ie)
# 		# end=e
# 		# p=[]
# 		# p.append(floor(e))
# 		# e=1/(e-floor(e))
# 		# while e!=end:
# 		# 	ie=floor(e)
# 		# 	p.append(ie)
# 		# 	e=1/(e-ie)
# 		# l=p
# 		# s+=p+p
# 	sa=[]
# 	ai=iter(get_as())
# 	def get_a(w):
# 		# print(w)
# 		while len(sa)<=w:
# 			sa.append(next(ai))
# 		return sa[w]

# 	# n=[e,1]
# 	# def get_n(w):
# 	# 	if len(n)>w:
# 	# 		return n[w]
# 	# 	for e in range(len(n),w):
# 	# 		get_n(e)
# 	# 	n.append(n[w-2] % n[w-1])
# 	# 	return n[w]
# 	# def get_a(w):
# 		# print(w)
# 		if w<len(s):
# 			a=s[w]
# 		else:
# 			a=l[(w-len(s))%len(l)]
# 		return a
# 		# return get_n(w)//get_n(w+1)

# 	p_2=get_a(0)
# 	q_2=1
# 	p_1=get_a(0)*get_a(1)+1
# 	q_1=get_a(1)
# 	for w in range(2,9999):
# 		a=get_a(w)
# 		p=a*p_1+p_2
# 		q=a*q_1+q_2
# 		p_1,p_2=p,p_1
# 		q_1,q_2=q,q_1
# 	return Fraction(p,q)

def fast_root2(q):
	if type(q)==Fraction:
		return root(q.numerator)/root(q.denominator)
	if type(q)==froot:
		return q.as_fraction()
	if type(q)!=int:
		return root(Fraction(q))
	if q==0:
		return Fraction(0)
	e=float(q)**0.5
	# if e.b==0:
	# 	return e.a

	a=[]
	ie=floor(e)
	a.append(ie)
	e=1/(e-ie)
	ie=floor(e)
	a.append(ie)
	e=1/(e-ie)

	p_2=a[0]
	q_2=1
	p_1=a[0]*a[1]+1
	q_1=a[1]

	n=[float(q)**0.5]
	n.append(n[0]*0+1)
	m=divmod(n[0],n[1])
	n=[n[1],m[1]]
	m=divmod(n[0],n[1])
	n=[n[1],m[1]]
	for w in range(2,9999):
		m=divmod(n[0],n[1])
		n=[n[1],m[1]]
		a=m[0]

		p=a*p_1+p_2
		q=a*q_1+q_2
		p_1,p_2=p,p_1
		q_1,q_2=q,q_1
	return Fraction(p,q)

def floor_root(q):
	r=0
	p=1
	while p<q:
		p<<=32
	u=0
	while p:
		u=r+p
		if q >= u :
			q-=u
			r+=p
			r+=p
		r>>=1
		p>>=2
	return r

def fraction_root(q):
	if type(q)==Fraction:
		return fraction_root(q.numerator)/fraction_root(q.denominator)
	if type(q)==froot:
		return q.as_fraction()
	if type(q)!=int:
		return fraction_root(Fraction(q))
	p=2**14
	# p=2**p
	return Fraction(floor_root(q<<p<<p),1<<p)
