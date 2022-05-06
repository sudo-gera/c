from h import *

o=Fraction(1)

def run(a,s,d,f):
	if d+f>14:
		s=0
		s+=run(a+1,s,d-1,f)*o*d/(d+f)
		s+=run(a,s+1,d,f-1)*o*f/(d+f)
		return s
	else:
		return o*a/(a+s)

print(run(26,5,15,4))
