n=int(input())
n//=2
k=0
c=1
m=10**9+7
while k<n:
	k+=1
	c=2*(2*k-1)*c*pow(k+1,m-2,m)%m
print(c%m)
