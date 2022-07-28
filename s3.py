from bisect import *
def bisect_in(a,s):
	return bisect_left(a,s)!=bisect_right(a,s)
primes=[2,3,5]
def is_prime_root(q):
	if primes[-1]>=q:
		return bisect_in(primes,q)
	for w in primes:
		if q%w==0:
			return False
		if w*w>q:
			return True
	start=primes[-1]
	start=start//6*6-1
	for w in count(start,6):
		if q%w==0:
			return False
		if q%(w+2)==0:
			return False
		if w*w>q:
			return True
def is_prime(q):
	if q<10**11:
		return is_prime_root(q)
	return is_prime_Miller(q)

def next_prime(q):
	if q<2:
		return 2
	q-=(q+1)%2
	q+=2
	while not is_prime(q):
		q+=2
	return q
def prev_prime(q):
	if q<3:
		return None
	if q==3:
		return 2
	q+=(q+1)%2
	q-=2
	while not is_prime(q):
		q-=2
	return q
def primes_until(w):
	while primes[-1]<w:
		primes.append(next_prime(primes[-1]))

primes_until(4*10**4)
a=input()
s=a
a=list(a)
if '*' not in a:
	if not is_prime(int(s)):
		print(s)
	else:
		print(-1)
else:
	c=0
	for w in range(len(a)):
		if a[w]=='*':
			if c==0:
				c=1
			else:
				a[w]='1'
	s=[q for q,w in enumerate(a) if w=='*'][0]
	d=0
	while 1:
		d+=1
		a[s]=str(d)
		z=int(''.join(a))
		if z%3==0:
			break
	print(''.join(a))
