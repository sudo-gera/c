from icecream import *
class treap_el:
	def __init__(s,v,f=[]):
		s.f=f
		s.r=[v for w in range(len(f))]
		s.v=v
		from random import random
		s.w=random()
		s._z=None
		s._x=None
		s.s=1

	@property
	def z(self):
		return self._z
	
	@z.setter
	def z(self,v):
		self._z=v
		update(self)

	@property
	def x(self):
		return self._x

	@x.setter
	def x(self,v):
		self._x=v
		update(self)

	def __repr__(s):
		return '\x1b[32m<\x1b[0m'+str(to_list(s))[1:-1]+'\x1b[32m>\x1b[0m'
		# return '\x1b[32m|\x1b[0m'+str(to_list(s))[1:-1]+'\x1b[32m\x1b[0m'

def repr_el(q):
	return repr([q.v]+q.f)


def tree(s,q=0):
	if s==None:
		ret=''
	else:
		ret=tree(s.z,q+1)+' '*q+repr(s.v)+'\n'+tree(s.x,q+1)
	return ret

def supertree(s,p=0):
	if isinstance(s,treap):
		return supertree(s.e,p)
	if s==None:
		r=[[]]
	elif s.z!=None and s.x!=None:
		z=supertree(s.z,1)
		x=supertree(s.x,1)
		if len(z[0])>len(x[0]):
			for w in range(len(x)):
				x[w]+=[' ']*(len(z[0])-len(x[w]))
		if len(x[0])>len(z[0]):
			for w in range(len(z)):
				z[w]+=[' ']*(len(x[0])-len(z[w]))
		r=z+[[' ']*len(z[0])]+x
		u=0
		for q in range(len(r)):
			if r[q] and r[q][0]==' ':
				if u%2:
					if q==len(z):
						r[q]=[repr_el(s),'┫']+r[q]						
					else:
						r[q]=[' ','┃']+r[q]
				else:
					r[q]=[' ',' ']+r[q]
			elif u==0:
				u+=1
				r[q]=[' ','┏']+r[q]
			else:
				u+=1
				r[q]=[' ','┗']+r[q]
	elif s.z!=None:
		z=supertree(s.z,1)
		x=[]
		r=z+[[' ']*len(z[0])]+x
		u=0
		for q in range(len(r)):
			if r[q] and r[q][0]==' ':
				if u%2:
					if q==len(z):
						r[q]=[repr_el(s),'┛']+r[q]
					else:
						r[q]=[' ','┃']+r[q]
				else:
					r[q]=[' ',' ']+r[q]
			elif u==0:
				u+=1
				r[q]=[' ','┏']+r[q]
			else:
				u+=1
				r[q]=[' ','┗']+r[q]
	elif s.x!=None:
		z=[]
		x=supertree(s.x,1)
		r=z+[[' ']*len(x[0])]+x
		u=1
		for q in range(len(r)):
			if r[q] and r[q][0]==' ':
				if u%2:
					if q==len(z):
						r[q]=[repr_el(s),'┓']+r[q]
					else:
						r[q]=[' ','┃']+r[q]
				else:
					r[q]=[' ',' ']+r[q]
			elif u==0:
				u+=1
				r[q]=[' ','┏']+r[q]
			else:
				u+=1
				r[q]=[' ','┗']+r[q]
	else:
		r=[[repr_el(s)]]
	if p:
		return r
	for w in range(len(r[0])):
		ml=len(max([e[w] for e in r],key=len))
		for e in range(len(r)):
			r[e][w]=(r[e][w]+' '*ml)[:ml]
	r=[''.join(w) for w in r]
	r='\n'.join(r)+'\n'
	return r

def get_by_index(s,n):
	if s==None:
		raise IndexError
	if s.z==None:
		if n==0:
			return s
		else:
			return get_by_index(s.x,n-1)			
	else:
		if n==s.z.s:
			return s
		if n<s.z.s:
			return get_by_index(s.z,n)
		if n>s.z.s:
			return get_by_index(s.x,n-s.z.s-1)

def contains(s,v):
	return s!=None and (s.v==v or contains(s.z,v) or contains(s.x,v))

def index(s,v,t=0):
	if s==None:
		ret=None
	else:
		ret=index(s.z,v,1)
		if ret==None:
			if s.v==v:
				if s.z==None:
					ret=0
				else:
					ret=s.z.s
			else:
				ret=index(s.x,v,1)
				if ret!=None:
					if s.z==None:
						ret+=1
					else:
						ret+=s.z.s+1
	if t==0:
		if ret==None:
			raise ValueError
	return ret


def count(s,v):
	if s==None:
		return 0
	return count(s.z,v)+(s.v==v)+count(s.x,v)

def part_f(s,f,b,e):
	if b==0 and e==s.s:
		if f not in s.f:
			add_f(s,f)
		try:
			return s.r[s.f.index(f)]
		except:
			print(s.f,f)
	if s.z==None:
		if b<1:
			if s.x!=None:
				return f([s.v,part_f(s.x,f,b,e-1)])
			else:
				return s.v
		else:
			return part_f(s.x,f,b-1,e-1)
	if e<=s.z.s:
		return part_f(s.z,f,b,e)
	if s.z.s==e-1:
		if b<s.z.s:
			return f([part_f(s.z,f,b,s.z.s),s.v])
		else:
			return s.v
	if b<s.z.s<e-1:
		return f([part_f(s.z,f,b,s.z.s),s.v,part_f(s.x,f,0,e-s.z.s-1)])
	if s.z.s==b:
		if s.z.s+1<e:
			return f([s.v,part_f(s.x,f,0,e-s.z.s-1)])
		else:
			return s.v
	if s.z.s<b:
		return part_f(s.x,f,b-s.z.s-1,e-s.z.s-1)

def add_f(t,f):
	if t==None:
		return
	if f not in t.f:
		t.f.append(f)
		add_f(t.z,f)
		add_f(t.x,f)
		update(t)

def to_list(s):
	if s==None:
		return []
	a=to_list(s.z)
	a.append(s.v)
	a+=to_list(s.x)
	return a

def update(t):
	if t==None:
		pass
	elif t.z==t.x==None:
		t.s=1
		t.r=[t.f[w]([t.v]) for w in range(len(t.f))]
	elif t.z==None:
		t.s=t.x.s+1
		t.r=[t.f[w]([t.v,t.x.r[w]]) for w in range(len(t.f))]
	elif t.x==None:
		t.s=t.z.s+1
		t.r=[t.f[w]([t.z.r[w],t.v]) for w in range(len(t.f))]
	else:
		t.s=t.z.s+t.x.s+1
		t.r=[t.f[w]([t.z.r[w],t.v,t.x.r[w]]) for w in range(len(t.f))]

def merge(t1,t2):
	if t1==None:
		return t2
	if t2==None:
		return t1
	if t1.f!=t2.f:
		f=[]
		for w in t1+t2:
			if w not in f:
				f.append(w)
		t1=treap(treap(t1,f=f)).e
		t2=treap(treap(f2,f=f)).e
	if t1.w<t2.w:
		t2.z=merge(t1,t2.z)
		return t2
	else:
		t1.x=merge(t1.x,t2)
		return t1

def split(t,n):
	if t==None:
		return [None,None]
	elif t.z==None:
		if n<1:
			return [None,t]
		else:
			t.x,t2=split(t.x,n-1)
			return [t,t2]
	elif t.z.s==n:
		t1=t.z
		t.z=None
		return [t1,t]
	elif t.z.s==n-1:
		t2=t.x
		t.x=None
		return [t,t2]
	elif t.z.s<n:
		t.x,t2=split(t.x,n-t.z.s-1)
		return [t,t2]
	elif t.z.s>n:
		t1,t.z=split(t.z,n)
		return [t1,t]

from functools import total_ordering
@total_ordering
class treap:
	def __init__(s,l=[],f=[]):
		if isinstance(l,treap_el):
			s.e=l
		else:
			s.f=f
			l=list(l)
			s.e=None
			for w in l:
				s.e=merge(s.e,treap_el(w,f=f))

	def __contains__(s,v):
		return contains(s.e,v)

	def __len__(s):
		return s.e.s if s.e!=None else 0

	def __str__(s):
		return '<'+repr(s.to_list())[1:-1]+'>'

	def __getitem__(s,n):
		if type(n)==slice:
			if n.start==None:
				n=slice(0,n.stop,n.step)
			if n.stop==None:
				n=slice(n.start,len(s),n.step)
			if n.step in s.f:
				return part_f(s.e,n.step,n.start,n.stop)
			else:
				q,e=split(s.e,max(n.start,n.stop))
				q,w=split(q,min(n.start,n.stop))
				if n.step==0:
					r=treap(w)
					w=None
				else:
					r=treap(treap(w).to_list()[::n.step])
				w=merge(w,e)
				s.e=merge(q,w)
				return r
		else:
			if n<0:
				n+=len(s)
			return get_by_index(s.e,n).v

	def __setitem__(s,n,v):
		if type(n)==slice:
			if n.start==None:
				n=slice(0,n.stop,n.step)
			if n.stop==None:
				n=slice(n.start,len(s),n.step)
			q,e=split(s.e,max(n.start,n.stop))
			q,w=split(q,min(n.start,n.stop))
			w=treap(v).e
			w=merge(w,e)
			s.e=merge(q,w)
		else:
			if n<0:
				n+=len(s)
			get_by_index(s.e,n).v=v

	def __delitem__(s,n):
		if type(n)==slice:
			if n.start==None:
				n=slice(0,n.stop,n.step)
			if n.stop==None:
				n=slice(n.start,len(s),n.step)
			q,e=split(s.e,max(n.start,n.stop))
			q,w=split(q,min(n.start,n.stop))
			s.e=merge(q,e)
		else:
			q,w=split(s.e,n%len(s))
			w,e=split(w,1)
			s.e=merge(q,e)

	def __cmp__(s,d):
		try:
			q=iter(s)
			w=iter(d)
		except:
			return float('nan')
		while 1:
			e,r=0,0
			try:
				z=next(q)
				e=1
			except:
				pass
			try:
				x=next(w)
				r=1
			except:
				pass
			if e>r:
				return 1
			if e<r:
				return -1
			if e:
				if z>x:
					return 1
				if z<x:
					return -1
			else:
				return 0

	def __lt__(s,d):
		return s.__cmp__(d)<0

	def __eq__(s,d):
		return s.__cmp__(d)==0

	def __iadd__(s,a):
		if isinstance(a,treap):
			s.e=merge(s.e,a.e)
			return s
		else:
			s+=treap(a)

	def __add__(s,d):
		a=treap(s)
		a+=d
		return a

	def __mul__(s,a):
		return treap(s.to_list()*a)

	def __imul__(s,a):
		return treap(s.to_list()*a)

	def clear(s):
		s.e=None

	def append(s,a):
		s+=[a]

	def copy(s):
		return treap(s.to_list())

	def count(s,v):
		return count(s.e,v)

	def extend(s,*v):
		for w in v:
			s+=w
		return s

	merge=extend

	def split(s,*n):
		q=s.e
		s.e=None
		r=[]
		for w in n[::-1]:
			r.append(0)
			q,r[-1]=split(q,w)
		r.append(q)
		r=[treap(w) for w in r[::-1]]
		return r

	def index(s,v):
		return index(s.e,v)

	def insert(s,n,v):
		if n<0:
			n+=len(s)
		q,w=split(s.e,n)
		q=merge(q,treap_el(v))
		s.e=merge(q,w)

	def pop(s):
		s.e,q=split(s.e,len(s)-1)
		return q.v

	def remove(s,v):
		del(s[s.index(v)])

	def sort(s,key=None,reverse=False):
		s.e=treap(sorted(s.to_list())).e

	def to_list(s):
		return to_list(s.e)

	def reverse(s):
		a=s.to_list()
		a.reverse()
		return treap(a)

	@property
	def r(s):
		return s.e.r

prod=lambda a:a[0]*(a+[1,1])[1]*(a+[1,1])[2]
a=treap([1,2,3,4,5,6,7])

print(supertree(a))

try:
	print(part_f(a.e,sum,2,5))
except:
	pass

print(supertree(a))







