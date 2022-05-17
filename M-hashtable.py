from sys import stdin
s=stdin.read().split()
d=[None]*10
while s:
	if s[0]=='create':
		if d[int(s[1])]==None:
			d[int(s[1])]={}
		s=s[2:]
	elif s[0]=='insert':
		t=int(s[1])
		if d[t]!=None:
			d[t][s[2]]=s[3]
		s=s[4:]
	elif s[0]=='erase':
		t=int(s[1])
		if d[t]!=None:
			if s[2] in d[t]:
				del d[t][s[2]]
		s=s[3:]
	elif s[0]=='find':
		t=int(s[1])
		if d[t]!=None:
			if s[2] in d[t]:
				print(d[t][s[2]])
			else:
				print('MISSING')
		else:
			print('MISSING')
		s=s[3:]
	elif s[0]=='destroy':
		t=int(s[1])
		d[t]=None
		s=s[2:]
	else:
		print(s)
		assert 0
