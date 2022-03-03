from queue import Queue
scan_cache=Queue()
def scan(*t):
	t=list(t)
	if len(t)==0:
		t.append(int)
	global scan_cache
	while scan_cache.qsize()<len(t):
		for w in input().split():
			scan_cache.put(w)
	t=[w(scan_cache.get_nowait()) for w in t]
	if len(t)==1:
		return t[0]
	return t
