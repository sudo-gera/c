from h import *
def root(q):
	r=0
	p=1
	while p<q:
		p *= 4
	while p:
		u=p+r
		if q>=u:
			q-=u
			r+=p
			r+=p
		r //= 2
		p //= 4
	return r


print(all([root(w) == floor_root(w) for w in range(-9999,999999)]))
