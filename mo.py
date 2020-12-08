n=int(input())
a=list(map(int,input().split()))
s=[0,sum(a)]
c=0
for w in range(len(a)):
	s.append(s[-1]*2-s[-2]-a[c]-a[-1-c])
	c+=1
print(*s[1:-1])