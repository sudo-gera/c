from functools import *
try:
	cache
except:
	cache=lru_cache(maxsize=None)
@cache
def fibonacci(n,m=None):
	t=1
	while t<n:
		t<<=1
	f0=0
	f1=1
	while t>1:
		if n&t:
			f1+=f0
			f0=f1-f0
		f0,f1=f1*f0*2-f0*f0,f0*f0+f1*f1
		if m:
			f0%=m
			f1%=m
		t>>=1
	return [f0,f1][n%2]
