from h import *

# =(fib_one(l-2,m)*fib_one(k,m)+fib_one(l-1,m)*fib_one(k+1,m))

# f[k+l-1]=f[l-1-1]*f[k-1]+f[l-1]*f[k+1-1]
# o[k+l]=o[l-1]*o[k]+o[l]*o[k+1]
# o[n//2+n//2+n%2]=o[n//2+n%2-1]*o[n//2]+o[n//2+n%2]*o[n//2+1]
# if n%2:
# 	o[n]=o[n//2]*o[n//2]+o[n//2+1]*o[n//2+1]
# else:
# 	o[n]=o[n//2-1]*o[n//2]+o[n//2]*o[n//2+1]
# o[2*n]=o[n-1]*o[n]+o[n]*o[n+1]
# o[2*n+1]=o[n]*o[n]+o[n+1]*o[n+1]
# o[2*n]=(o[n+1]-o[n])*o[n]+o[n]*o[n+1]
# o[2*n+1]=o[n]*o[n]+o[n+1]*o[n+1]



@cache
def fib(n,m=10**6):
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
		f0%=m
		f1%=m
		t>>=1
	return [f0,f1][n%2]


for w in range(9999):
	n=rand()
	if fib(n,1000000)!=fibonacci(n,1000000):
		print(w)
		break
