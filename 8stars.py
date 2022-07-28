scan_cache=[]
def scan(t=int):
	global scan_cache
	while not scan_cache:
		scan_cache+=input().split()
	q=scan_cache[0]
	scan_cache=scan_cache[1:]
	return t(q)

n=scan()
s=[[[0 for w in range(n)] for w in range(n)] for w in range(n)]
while 1:
	m=scan()
	if m==1:
		x,y,z,k=scan(),scan(),scan(),scan()
		s[x][y][z]+=k
	elif m==2:
		x1,y1,z1,x2,y2,z2=scan(),scan(),scan(),scan(),scan(),scan()
		res=0
		for w in range(x1,x2+1):
			for e in range(y1,y2+1):
				for r in range(z1,z2+1):
					res+=s[w][e][r]
		print(res)
	else:
		break
