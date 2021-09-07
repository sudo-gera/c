p=10**9+9
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
[print(inv(int(input()))) for w in range(int(input()))]