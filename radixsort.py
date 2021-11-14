def radixsort(A):
	n=len(A)
	m=min(A)
	A=[w-m for w in A]
	for w in range(len(str(max(A)))+4):
		k=10
		B=[0]*n
		C=[0]*k
		for i in range(k):
			C[i] = 0;
		for i in range(n):
			C[(A[i])//10**w%k] += 1;
		for j in range(1,k):
			C[j] += C[j - 1];
		for i in range(n-1,-1,-1):
			C[(A[i])//10**w%k] -= 1;
			B[C[(A[i])//10**w%k]] = A[i];
		A=B
	A=[w+m for w in A]
	return A



for w in range(1000):
	q=list(range(-10**2,10**2))
	from random import shuffle
	shuffle(q)
	if not sorted(q)==radixsort(q):
		print(q)
