try:
	from icecream import ic
except:
	ic = lambda *a: None if not a else a[0] if len(a) == 1 else a
def run(s):
	s=s.upper()
	a=["I","II","III","V","X","XIX","XX","XXX","L","C","CXC","CC","CCC","D","M","MCM","MM","MMM"]
	a.sort(key=len)
	a=a[::-1]

	res=[]

	w=0
	while w<len(s):
		for e in a:
			if s[w:w+4].startswith(e):
				if \
					(len(e)!=2 or s[w+2:w+5] not in 'XIX CXC MCM'.split())\
					\
					:
					res.append(s[w:w+len(e)])
					w+=len(e)
					break
	return res

n=input()
try:
	n=int(n)
	s=input()
except:
	s=n
res=run(s)
print(len(res))
for w in res:
	print(w)
