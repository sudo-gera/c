#from sys import argv
n=int(input())
a=[]
for y in range(n):
	a.append([])
	for x in range(n):
		m=(x+y-n//2)
		b=(x-y-n//2)-m*(n-3)
		m%=n
		b%=n
		if b%2:
			b+=n
		b//=2
		e=m*n+b+1
		a[-1].append(e)
		print(e,end='\t')
#		print('\x1b[9'+str(m%7+1)+'m',m%n,b%n,end='\t')
	print()

#	s=[sum(w) for w in a]+[sum(w) for w in zip(*a)]+[sum([a[w][w] for w in range(len(a))])]+[sum([a[w][len(a)-1-w] for w in range(len(a))])]
#	if len(set(s))!=1:
#		print(n)