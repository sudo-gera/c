from h import *
def root(q):
	# x=Fraction(q)
	# for w in range(9):
	# 	x=(x*x+q)/2/x
	# 	print(float(x))
	# return x
	xn=q
	xd=1
	for w in range(1):
		xn=xn*xn+xd*xd*q
		xd=xd*xn*2
		print(xn,xd)
		print(xn/xd)
	return Fraction(xn,xd)
