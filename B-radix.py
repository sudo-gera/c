from h import *
p=scan()
q=scan()
f=Fraction(p,q)
n=2
while p:
	p*=n
	n+=1
	print(p//q,end=' ')
	p%=q
print()
