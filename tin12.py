n=int(input())
a=[int(w) for w in input().split()]
s=1
for w in a:
	if s==w:
		s+=1
s-=1
if s==0:
	print(-1)
else:
	print(s)
