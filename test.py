from h import *
def floor_root(q):
	q=int(q)
	r=0
	p=1
	while p<q:
		p<<=32
	while p:
		u=r+p
		if q >= u :
			q-=u
			r+=p
			r+=p
		r>>=1
		p>>=2
	return r

while 1:
	print(floor_root(scan()))
