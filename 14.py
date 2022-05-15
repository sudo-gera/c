a=[0]
input()
s=input()
for q,w in enumerate(s):
	d=a.index(q)
	if w=='L':
		a=a[:d]+[q+1]+a[d:]
	else:
		d+=1
		a=a[:d]+[q+1]+a[d:]
for w in a:
	print(w,end=' ')
print()
