a=int('8503',16)
b=int('5925',16)
def mod(a,s):
	d=abs(a)%abs(s)
	if a<0:
		d=-d
	return d
def div(a,s):
	return (a-mod(a,s))//s

print(hex( max( mod(a**2,b),div(-16+a**2,b) ) )[2:])