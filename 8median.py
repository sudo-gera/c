from bisect import *
n=int(input())
a=[]
for w in range(n):
	s=[int(w) for w in input().split()]
	if s[0]:
		if a:
			print(a[(len(a)+1)//2-1])
		else:
			print(0)
	else:
		insort(a,s[1])
