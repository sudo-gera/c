from h import *
m,n=scan(),scan()
d={}
for w in range(n):
	name,score=scan(str),scan()
	if name in d:
		if d[name][0]<score:
			d[name]=[score,w]
	else:
		d[name]=[score,w]
assert len(d)==m
d=[
	[-d[w][0],d[w][1],w]
for w in d]
d.sort()
for w in d:
	print(w[2])
