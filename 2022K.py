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

n=scan(int)
r=1
for w in range(1,n+1):
    while w%10==0:
        w//=10
    r*=w
    while r%10==0:
        r//=10
    r%=1000
if r>=100:
    print("%02i"%(r%100))
else:
    print(r)