n=int(input())+1
c=0
for w in range(1,int(n**0.5)+4):
	if w*w<n and n%w==0:
		c+=2
	if w*w==n and n%w==0:
		c+=1
print(c)