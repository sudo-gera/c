n,k=list(map(int,input().split()))
from math import factorial
def ff(q):
	if q>10:
		return 0
	return factorial(q)
print((ff(n)-ff(k))%10)