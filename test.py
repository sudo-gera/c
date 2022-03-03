for w in range(128):
	from h import *
	a=rand(2**32)
	a=fast_next_prime(a)
	if not is_prime(a):
		print(a)
		assert(0)
