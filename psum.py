a=[1,2,3,4,5]
bs=a[:]+[0]
bs[0]=0
for w in range(len(a)):
	bs[w+1]=bs[w]+a[w]
es=a[:]+[0]
es[-1]=0
for w in range(len(a)-1,-1,-1):
	es[w]=es[w+1]+a[w]
ps=sum(a)
def psum(s,f):
	return ps-bs[s]-es[f]
for w in [[0,5],[1,4],[0,4],[1,5]]:
	print(a[w[0]:w[1]],psum(*w))
