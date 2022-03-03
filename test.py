from h import *
def t(q):
	return [len([
					e
			for e in range(w)
				if q[e]>q[w]])
		for w in range(len(q))
	]
def r(q):
	for w in permutations(range(len(q))):
		if t(w)==q:
			return [e+1 for e in w]
def f(q):
	if len(q)==0:
		return []
	a=f(q[:-1])
	if a==None:
		return None
	if not 0<=len(a)-q[-1]<=len(a):
		return None
	a=a[:len(a)-q[-1]]+[len(q)]+a[len(a)-q[-1]:]
	if t(a)==q:
		return a

def z(q):
	# if len(q)==0:
	# 	return []
	# a=f(q[:-1])
	a=[]
	for w in range(0,len(q)):
		if not w>=q[w]>=0:
			return None
		a[w-q[w]:w-q[w]]=[w+1]
	if t(a)==q:
		return a


# a=[int(w) for w in input().split()]
# assert f(a)==z(a)
n=scan()
a=[scan() for w in range(n)]
a=r(a)
if a==None:
	print('IMPOSSIBLE')
else:
	for w in a:
		print(w,end=' ')
	print()
