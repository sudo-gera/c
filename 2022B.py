from queue import Queue
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


a=scan([int]*4)
from itertools import permutations
print(0+bool([(q,w,e,r) for q,w,e,r in permutations(a) if q*r==w*e and q+e>w+r and q<w+e+r and e<q+w+r]))

