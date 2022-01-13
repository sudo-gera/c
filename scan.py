scan_cache=[]
def scan(t=int):
	global scan_cache
	while not scan_cache:
		scan_cache+=input().split()
	q=scan_cache[0]
	scan_cache=scan_cache[1:]
	return t(q)
