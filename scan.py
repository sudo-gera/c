from queue import Queue
scan_cache=Queue()
def scan(*t):
	t=list(t)
	global scan_cache
	while scan_cache.qsize()<len(t):
		for w in input().split():
			scan_cache.put(w)
	if len(t)==0:
		t.append(int)
	t=[w(scan_cache.get()) for w in t]
	if len(t)==1:
		return t[0]
	return t
