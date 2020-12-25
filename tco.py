n,d=list(map(int,input().split()))
x=list(map(int,input().split()))
x.sort()
from bisect import *
c=0
for w in x:
	if bisect_left(x,w+d)!=bisect_right(x,w+d):
		c+=1
print(c)