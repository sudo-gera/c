from h import *

o=Fraction(1)

r=0
for w in range(100):
	print(w+1,100-w,w,99-w)
	r+=(w)*(100-w)+(w+1)*(99-w)
	print(w+1,99-w,w+1,99-w)
	r+=(w+1)*(99-w)+(w+1)*(99-w)
print(r)
