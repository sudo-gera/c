def rn(n):
	b=[]
	while n:
		b.append(n%2)
		n//=2
	b=b[::-1]
	b.append(b[-2])
	b.append(b[1])
	b=b[::-1]
	b=[b[w]*2**w for w in range(len(b))]
	return sum(b)

for w in range(2,40):
	print(w,rn(w))