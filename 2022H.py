# from h import *
from pprint import pprint
from queue import Queue
from bisect import *
scan_cache=Queue()
def scan(t=int):
	if type(t) in (list, tuple):
		t=type(t)([scan(w) for w in t])
		return t
	global scan_cache
	while scan_cache.empty():
		for w in input().split():
			scan_cache.put(w)
	return t(scan_cache.get_nowait())

k=scan()
a=scan([(int,int)]*k)
a.sort()
s=[[w,[],1] for w in a]
for e,r in enumerate(a):
    q,w=r
    for o in [
        (q-1,w),
        (q,w-1),
        (q+1,w),
        (q,w+1),
    ]:
        bl=bisect_left(a,o)
        if bl!=bisect_right(a,o):
             s[e][1].append(bl)
f=set(range(len(a)))
c=0
while f:
    c+=1
    q=Queue()
    t=next(iter(f))
    q.put(t)
    while not q.empty():
        k=q.get()
        if s[k][2]:
            for w in s[k][1]:
                q.put(w)
            s[k][2]=0
            f.remove(k)
print(pow(2,c,998_244_353))





