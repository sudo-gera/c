def next_permutation(a):
	"""Generate the lexicographically next permutation inplace.

	https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
	Return false if there is no next permutation.
	"""
	# Find the largest index i such that a[i] < a[i + 1]. If no such
	# index exists, the permutation is the last permutation
	for i in reversed(range(len(a) - 1)):
		if a[i] < a[i + 1]:
			break  # found
	else:  # no break: not found
		return False  # no next permutation

	# Find the largest index j greater than i such that a[i] < a[j]
	j = next(j for j in reversed(range(i + 1, len(a))) if a[i] < a[j])

	# Swap the value of a[i] with that of a[j]
	a[i], a[j] = a[j], a[i]

	# Reverse sequence from a[i + 1] up to and including the final element a[n]
	a[i + 1:] = reversed(a[i + 1:])
	return True


def main(n,k):
	from math import factorial
	a=list(range(n))
	fac=[factorial(w) for w in range(15)]
	k%=fac[n]
	while 1:
		if k==0:
			return a
		b=[w for w in fac if w-1<=k][-1]
		b=fac.index(b)
		a=a[:-b]+a[-b:][::-1]
		k-=fac[b]-1
		if k==0:
			return a
		next_permutation(a)
		k-=1

n=int(input())
k=int(input())
a=main(n,k-1)
print(*[w+1 for w in a])