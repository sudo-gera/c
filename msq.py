n=int(input())
for y in range(n):
	for x in range(n):
		m=(x+y-n//2)
		b=(x-y-n//2)-m*(n-3)
		m%=n
		b%=n
		b+=b%2*n
		b//=2
		e=m*n+b+1
		print(e,end='\t')
	print()
