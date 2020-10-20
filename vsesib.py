n=int(input())
a=[list(map(int,input().split())) for w in range(n)]
from math import atan2,pi
a=[[atan2(w[0],w[1])/pi,w[0]**2+w[1]**2,*w] for w in a]
a=[[w[0] if w[0]>0 else w[0]+1,*w[1:]] for w in a]
a=[[w[0]-0.5 if w[0]>0.5 else w[0],*w] for w in a]
a.sort()
b=0
e=0
def same(a,s):
	return a[0]==s[0] and a[2]==s[2]
ext=0
while b<len(a):
	while e<len(a) and same(a[b],a[e]):
		e+=1
	c1,c2=0,0
	for w in range(b,e):
		if a[w][0]==a[w][1]:
			c1+=1
		else:
			c2+=1
	ext+=c1*(c1-1)*c2*(c2-1)//4*8
	b=e
print(ext)