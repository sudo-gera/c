from h import *
p=scan()
q=scan()
n=2
f=2
a=Fraction(p,q)
while a:
	d=floor(a*f)
	print(d,end=' ')
	a-=d/f
	n+=1
	f*=n
print()
