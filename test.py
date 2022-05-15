from h import *

o=Fraction(1)


s=0
for w in range(21):
	for e in range(21):
		r=e*2+w
		if gcd(w,e)==1:
			if r*3<=20:
				if r*4>20:
					s+=o*r/w
					# s+=1/(o*e/w*2+1)
					print(w,e,r)
print(s)
