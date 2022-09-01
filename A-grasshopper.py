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

n,m=scan([int,int])
a=[0]*(n+m+n+m)
a[0]=1
q=0
while q<=n:
    for w in range(1,m+1):
        a[q+w]+=a[q]
    q+=1
print(a[n])