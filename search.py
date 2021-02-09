from bisect import *
class fa:
	def __init__(s,f,b,e,d):
		s.f=f
		s.b=b
		s.e=e
		s.d=d
	def __getitem__(s,a):
		return s.f(s.b+a/s.d)
	def __len__(s):
		return (s.e-s.b)*s.d
def bl(f,b,e,d,o):
	return bisect_left(fa(f,b,e,d),o)/d+b
def br(f,b,e,d,o):
	return bisect_right(fa(f,b,e,d),o)/d+b
def tl(f,b,e,d,o):
	return bisect_left(fa(lambda a:(f(a+1/d)-f(a-1/d))*d/2,b,e,d),o)/d+b
def tr(f,b,e,d,o):
	return bisect_right(fa(lambda a:(f(a+1/d)-f(a-1/d))*d/2,b,e,d),o)/d+b
