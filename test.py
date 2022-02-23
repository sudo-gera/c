from h import *
def root(q):
	x=Fraction(q)
	for w in range(10):
		x=(x+q/x)/2
	return x
	# xn=q
	# xd=1
	# for w in range(30):
	# 	xn,xd=xn*xn+xd*xd*q,xd*xn*2
	# 	t=gcd(xn,xd)
	# 	xn//=t
	# 	xd//=t
	# return Fraction(xn,xd)
