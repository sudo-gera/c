from h import *
mm=-1
while 1:
	d=rand(11)
	a=rand(11)
	c=10-a
	b=10-d
	if a+b==0 or c+d==0:
		continue
	m=Fraction(a,a+b)+Fraction(c,c+d)
	m/=2
	if m>mm:
		mm=m
		print(a,b,c,d,m)
