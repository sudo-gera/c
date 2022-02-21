from scan import scan
s=None
size=0
while 1:
	q=0
	w=0
	r=0
	e=0
	q=scan(int)
	if q==0 :
		w=scan(int)
		s=[0]*abs(w)
		size=0
		print(0)
	elif q==1:
		w=scan(int)
		if s!=None:
			if 0<=w<len(s):
				if s[w]==0:
					s[w]=1
					size+=1
				print(0)
			else:
				print(1)
		else:
			print(1)
	elif q==2:
		w=scan(int)
		if s!=None:
			if 0<=w<len(s):
				if s[w]==1:
					s[w]=0
					size-=1
				print(0)
			else:
				print(1)
		else:
			print(1)
	elif q==3:
		w=scan(int)
		if s==None:
			print(0)
		else:
			if 0<=w<len(s):
				print(s[w])
			else:
				print(0)
	elif q==4:
		s=None
		size=0
	elif q==5:
		if s==None:
			print(1)
		else:
			print(int(size==0))
	elif q==6:
		w=scan(int)
		if s==None:
			print(-1)
		else:
			if w>=0:
				for e in range(w,len(s)):
					if s[e]:
						print(e)
						break
				else:
					print(-1)
			else:
				print(-1)
	elif q==7:
		print(size)
	elif q==8:
		if s!=None:
			print([q for q,w in enumerate(s) if w])
	else:
		break;
