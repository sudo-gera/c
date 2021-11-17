from icecream import ic
a=open('stdin.txt').read().splitlines()
a=[w for w in a if w]
a=[w.split(':',1)[1].strip()[1:] for w in a]
a=[ [w[:w.index(']')],w[w.index(']')+1:]] for w in a  ]
a=[[e.split() for e in w] for w in a]
a=[[[int(r) for r in e] for e in w] for w in a]
h='0123456789abcdefghijklmnopqrstuvwxyz'
for w in range(len(a)):
	a[w][0]=int(''.join([h[e] for e in a[w][0][::-1]]),22)
for w in range(len(a)-1):
	if (a[w][0]+a[w][1][0]*a[w][1][1]*22**(a[w][1][2]+a[w][1][3]))!=(a[w+1][0]):
		print(w)
