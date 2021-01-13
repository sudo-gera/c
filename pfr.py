n,m=list(map(int,input().split()))
a=list(map(int,input().split()))
s=[[0 for w in range(n+1)] for w in range(m+1)]
for h in range(n+1):
	for j in range(m+1):
		if h==0:
			s[j][h]=0
		elif j-a[h-1]<0:
			s[j][h]=s[j][h-1]
		else:
			s[j][h]=max([s[j][h-1],s[j-a[h-1]][h-1]+a[h-1]])
#print('YES' if s[-1][-1]==m else 'NO')
#print(s[-1][-1])
from pprint import pprint
pprint(s)