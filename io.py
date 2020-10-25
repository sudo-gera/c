n=int(input())
m=int(input())
k=int(input())
c=0
t=0
while m<n:
	g=m//((k+1)//2)*k
	c+=1
	if g<=m:
		print(-1)
		exit()
	m=g
print(c)