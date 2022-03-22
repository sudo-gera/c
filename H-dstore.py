from h import *
n=scan()
s=[scan() for w in range(n)]
s.sort(reverse=1)
while (len(s) and s[len(s)-1]==0):
	s.pop();
c=0
while len(s)>1:
	# print(s)
	d=-1
	if len(s)==2:
		d=s[1]
		c+=d;
		s[0]-=d;
		s[1]-=d;
	else:
		lc=0
		while lc<len(s)-1 and s[lc]==s[0]:
			lc+=1
		d=s[len(s)-1]
		if lc<len(s)-1 and (s[0]-s[lc])*lc<d:
			d=(s[0]-s[lc])*lc
		for w in range(lc):
			s[w]-=d//lc
		for w in range(lc-d%lc,lc):
			s[w]-=1
		s[len(s)-1]-=d
		c+=d
	while (len(s) and s[len(s)-1]==0):
		s.pop();
	# s.sort(reverse=1)
print(c);
