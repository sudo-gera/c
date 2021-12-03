m=0
def logmax(q):
	global m
	if q>m:
		m=q
		print(m)


def run(q,a):
	if q>=57:
		logmax(len(a))
		return
	if not [w for w in a if w*5==q*2 or w*2==q*5]:
		a.append(q)
		run(q+1,a)
		a.pop()
	run(q+1,a)
run(1,[])
