def run():
	a=int(input())
	b=int(input())
	c=int(input())
	d=int(input())
	e=int(input())
	f=int(input())
	if a*c*e!=b*d*f:
		print(-1)
		return
	from fractions import Fraction as F
	ab=F(1)
	ca=ab*e/f
	bc=ca*c/d
	if ab!=bc*a/b:
		print(-1)
		return
	if max([ab,bc,ca])*2<sum([ab,bc,ca]):
		print(1)
	else:
		print(-1)

run()
