def isp(q):
	d=0
	for w in range(1,q+1):
		if q%w==0:
			d+=1
	return d==2

for w in range(10**4,10**5):
	d=str(w)
	d=list(map(int,d))
	e=[isp(d[w-2]+d[w]) for w in range(5)]
	if all(e):
		print(w)