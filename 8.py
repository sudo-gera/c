n,k=[int(w) for w in input().split()]
d=[int(w) for w in input().split()]
d=[[w[1],w[0]] for w in enumerate(d)]
d.sort()
e=0
m=-1
mb=-1
me=-1
for b in range(len(d)):
	while e<len(d) and d[e][0]-d[b][0]<=k:
		e+=1
	if e-b>m:
		m=e-b
		mb=b
		me=e
print(me-mb)
for w in range(mb,me):
	print(d[w][1]+1,end=' ')
print()
