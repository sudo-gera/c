try:
	from h import *
except:
	ic = lambda *a: None if not a else a[0] if len(a) == 1 else a

a=["I","II","III","V","X","XIX","XX","XXX","L","C","CXC","CC","CCC","D","M","MCM","MM","MMM"]
a.sort(key=lambda s:len(s)*1000+abs(ord(s[0])-ord(s[len(s)//2])) )
a=a[::-1]


def run(s,ai,bb,ee):
	if ai==len(a):
		return []
	else:
		res=[]
		w=bb
		while w<ee:
			d=s.find(a[ai],w,ee)
			if d!=-1:
				res+=run(s,ai+1,w,d)
				res.append(a[ai])
				w=d+len(a[ai])
			else:
				res+=run(s,ai+1,w,ee)
				w=ee
		return res






n=input()
try:
	n=int(n)
	s=input()
except:
	s=n
s=s.upper()
res=run(s,0,0,len(s))
print(len(res))
for w in res:
	print(w)
