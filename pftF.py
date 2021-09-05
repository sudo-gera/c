p=10**9+7
# p=7
def inv(q):
	_p=p-2;
	r=1;
	while (_p):
		if (_p%2):
			r*=q;
			r%=p;
		_p//=2;
		q*=q;
		q%=p;
		r%=p;
	return r;


n,m,l=[int(w) for w in input().split()]
c=[1]
for k in range(1,n+1):
	c.append(c[-1]*(n-k+1)%p*inv(k)%p)
r=0
for mk in range(m,l*m+1,m):
	if mk<=n:
		r+=c[mk]
	r%=p
print(r)

