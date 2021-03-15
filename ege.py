def f(n):
	if n==0:
		return 0
	if n%3:
		return n+f(n-n%3)
	return n+f(n-3)

for w in range(23):
	print(w,f(w))