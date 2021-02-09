t=int(input())
for w in range(t):
	n,m,k,a,b=list(map(int,input().split()))
	t=[]
	v=[]
	for w in range(m):
		tv=list(map(int,input().split()))
		t.append(tv[0])
		v.append(v[2:])
	p=[]
	u=[]
	r=[]
	for w in range(k):
		tv=list(map(int,input().split()))
		p.append(tv[0])
		u.append(tv[1])
		r.append(tv[2])
	ps=[[[],[]] for w in range(n)]
	for h in range(n):
		for w in range(m):
			if h in v[w]:
				ps[h][0].append(w)
		for w in range(k):
			if h == p[w]:
				ps[h][1].append(w)
	