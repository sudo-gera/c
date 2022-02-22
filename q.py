from h import *
def ch(a,x):
	p=1
	while p<=a:
		p*=x
	return (a*a-a)%p==0

def find(x):
	return[
		a
	for a in range(10**7)
		if ch(a,x)
	][-1]
