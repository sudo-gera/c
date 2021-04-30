

print('-')
n=int(input())
a=[round(float(input())*10) for w in range(n)]
c=0
for w in range(len(a)):
	if a[w]>=10:
		print(w+1,end=' ')
		c=1
if c==0:
	print(1+a.index(max(a)))
else:
	print()
