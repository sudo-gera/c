from h import *
n=scan()
a=[set() for w in range(n)]
q=scan()
for w in range(q):
	c=scan(str)
	if c=='+':
		x,s=scan(),scan()
		a[s].add(x)
	if c=='-':
		x,s=scan(),scan()
		if x in a[s]:
			a[s].remove(x)
	if c=='=':
		s=scan()
		a[s]=set()
	if c=='?':
		s=scan()
		l=list(a[s])
		l.sort()
		if l:
			for w in l:
				print(w,end=' ')
		else:
			print(-1,end=' ')
		print()
	if c=='??':
		x=scan()
		printed=0
		for w in range(len(a)):
			if x in a[w]:
				print(w,end=' ')
				printed=1
		if not printed:
			print(-1,end=' ')
		print()
