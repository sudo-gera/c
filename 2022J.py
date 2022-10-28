def is_correst(a):
    c=0
    for w in a:
        if w=='(':
            c+=1
        if w==')':
            c-=1
        if c<0:
            return False
    return c==0

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

n,q=scan([int,int])
s=scan(str)
s=list(s)
for w in range(q):
    a,b=scan([int,int])
    s[a-1],s[b-1]=s[b-1],s[a-1]
    if is_correst(s):
        print("Yes")
    else:
        print("No")
    s[a-1],s[b-1]=s[b-1],s[a-1]


