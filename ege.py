a=[0]*1000
a[1]=1
for w in range(2,len(a)):
	p=[w-1,w-2]
	if w%3==0:
		p.append(w//3)
	if w>8:
		p=[e for e in p if e>=8]
	for e in p:
		a[w]+=a[e]
	a[10]=0
	a[11]=0
print(a[27])