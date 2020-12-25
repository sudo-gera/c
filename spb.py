from math import factorial
def c(n,k):
	if n>=0 and k>=0 and n-k>=0:
		return factorial(n)//factorial(k)//factorial(n-k)
	else:
		return 0
for n in range(300):
	e=0
	for k in range(2,n+1):
		e+=c(n,2)/c(k,2)
	if (n-1)**2<e:
		print(n,(n-1)**2,e)
