def ns(q):
	return [(q[0]+1,q[1]),(q[0]*3,q[1]),(q[0],q[1]+1),(q[0],q[1]*3)]
def win(q):	
	return sum(q)>=49
def nwin(q):
	return sum(q)<49
from functools import lru_cache
@lru_cache(maxsize=None)
def gwin(q):
	assert nwin(q)
	return any([win(w) or not gwin(w) for w in ns(q)])
for s in range(1,44):
	q=(5,s)
	if\
	nwin(q) and\
	gwin(q) and\
	any([
		nwin(w) and\
		any([
			win(e)
		for e in ns(w)])
	for w in ns(q)])\
	:
		print(s)
