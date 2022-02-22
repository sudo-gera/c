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
<<<<<<< HEAD
		s=[0]*w
=======
		s=[0]*abs(w)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
		size=0
		print(0)
	elif q==1:
		w=scan(int)
		if s!=None:
<<<<<<< HEAD
			if w<len(s):
=======
			if 0<=w<len(s):
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
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
<<<<<<< HEAD
			if w<len(s):
=======
			if 0<=w<len(s):
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
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
<<<<<<< HEAD
			if w<len(s):
=======
			if 0<=w<len(s):
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
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
<<<<<<< HEAD
			print(int(1 not in s))
=======
			print(int(size==0))
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	elif q==6:
		w=scan(int)
		if s==None:
			print(-1)
		else:
<<<<<<< HEAD
			for w in range(w,len(s)):
				if s[w]:
					print(w)
					break
=======
			if w>=0:
				for e in range(w,len(s)):
					if s[e]:
						print(e)
						break
				else:
					print(-1)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
			else:
				print(-1)
	elif q==7:
		print(size)
	elif q==8:
		if s!=None:
			print([q for q,w in enumerate(s) if w])
	else:
		break;
