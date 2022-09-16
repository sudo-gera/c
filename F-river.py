from h import *
n,p=scan(),scan()
a=[scan() for w in range(n)]
k=scan()
# print(a)
print(sum([w*w for w in a]))
for w in range(k):
	q,p=scan(),scan()-1
	if q==1:
		if p==0:
			a=[a[0]+a[1]]+a[2:]
		elif p==len(a)-1:
			a=a[:-2]+[a[-2]+a[-1]]
		else:
			a=a[:p-1]+[a[p-1]+a[p]//2,a[p+1]+(a[p]+1)//2]+a[p+2:]
	if q==2:
		a=a[:p]+[a[p]//2,(a[p]+1)//2]+a[p+1:]
	# print(a)
	print(sum([w*w for w in a]))
