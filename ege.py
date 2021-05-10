n=int(input())
a=[list(map(int,input().split())) for w in range(n)]
s=[max(w)%2 for w in a]
gs=[max(w) for w in a]
sb=sorted(s)[n//2]
ss=sum(s)%2
gss=sum(gs)
ci=-1
if sb!=ss:
	print(max([gss-max(a[w])+min(a[w]) for w in range(n) if sum(a[w])%2]))
else:
	print(gss)