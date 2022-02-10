from h import *
def root(q):
	p = 1
	while p<q:
		p *= 4
	r = 0
	while p:
		u=r+p
		if u<=q:
			q -= u
			r += p
			r += p
		r //= 2
		p //= 4
	return r


print(all([root(w) == floor_root(w) for w in range(-9999,9999)]))
