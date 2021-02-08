def ls(q):
	if q<2:
		return q-1
	return len(str(q))
def get(q):
	return -max([[ls(w)+ls(q-w),-w] for w in range(1,q)])[1]
db=[]
from bisect import *
def add(q):
	t=get(q)
	bl=bisect_left(db,[q,t])
	br=bisect_right(db,[q,t])
	if br==bl and (bl==0 or br==len(db) or db[bl-1][1]!=t or db[br][1]!=t):
		if bl>1 and db[bl-1][1]==t==db[bl-2][1]:
			db[bl-1][0]=q
		elif br<len(db)-1 and db[br][1]==t==db[br+1][1]:
			db[br][0]=q
		else:
			insort(db,[q,t])

