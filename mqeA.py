x1,y1,x2,y2=[int(w) for w in input().split()]
l=-1000
r=1000
for w in range(10**5):
	lc=(l*2+r)/3
	rc=(l+r*2)/3
	d,f=((x1-lc)**2+y1**2)**0.5+((x2-lc)**2+y2**2)**0.5,((x1-rc)**2+y1**2)**0.5+((x2-rc)**2+y2**2)**0.5

	if d<f:
		r=rc
	elif d>f:
		l=lc
	else:
		l=lc
		r=rc
print((r+l)/2)