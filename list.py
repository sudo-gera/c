from icecream import ic
class List_iterator:
	def __init__(s,**q):
		s.q=q
	@property
	def next(self):
		if 'next' not in self.q:
			self.q['next']=List_iterator(prev=self)
			return self.q['next']
		return self.q['next']
	@next.setter
	def next(self,v):
		self.q['next']=v
	@property
	def prev(self):
		if 'prev' not in self.q:
			self.q['prev']=List_iterator(next=self)
			return self.q['prev']
		return self.q['prev']
	@prev.setter
	def prev(self,v):
		self.q['prev']=v
	@property
	def value(s):
		return s.q['value']
	def __next__(s):
		s.q=s.next.q
		if 'value' not in s.q:
			raise StopIteration
		return s
	def __repr__(s):
		return f'{id(s.prev)%100}<-{id(s)%100}->{id(s.next)%100}'
def insert(q,v):
	v=List_iterator(value=v)
	v.next=q
	v.prev=q.prev
	q.prev.next=v
	q.prev=v
def remove(q):
	q.next.prev=q.prev
	q.prev.next=q.next
class List:
	def __init__(s,o=[]):
		s.e=s.b=List_iterator()
		for w in o:
			s.insert(s.e,w)
			# if s.e==s.b:
			# 	insert(s.e,w)
			# 	s.b=s.e.prev
			# else:
			# 	insert(s.e,w)
	class iter:
		def __init__(s,o):
			s.o=o.b.prev
		def __next__(s):
			s.o=s.o.next
			if 'value' not in s.o.q:
				raise StopIteration
			return s.o.value
	def __iter__(s):
		return s.iter(s)
	def insert(s,q,v):
		insert(q,v)
		if q==s.b:
			s.b=s.b.prev
	def remove(s,q):
		if q==s.b:
			s.b=s.b.next
		remove(q)
	def __iadd__(s,o):
		if isinstance(o,List):		
			s.e.prev.next=o.b
			o.b.prev=s.e.prev
			o.b=o.e=List_iterator()
			return s
		return s.__iadd__(List(o))
	def __repr__(s):
		return 'List('+repr(list(s))+')'
