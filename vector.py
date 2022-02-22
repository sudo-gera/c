from scan import scan
v=None
q=0
w=0
e=0
r=0
while (1):
	q=w=e=r=0
	q=scan(int)
<<<<<<< HEAD
	if (q==0):
		w=scan(int)
		if w<0:
			print(0)
		else:
			v=list(range(w))
			print(0)
=======
	print('-',q)
	if (q==0):
		w=scan(int)
		v=[0]*abs(w)
		print(0)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	elif (q==1):
		w=scan(int)
		if v==None:
			print(1)
		else:
			v.append(w)
			print(0)
	elif (q==2):
		if v==None:
			print(1,w)
		else:
			if v:
				w=v.pop()
				print(0,w)
			else:
				print(1,w)
	elif (q==3):
		print(int(not v))
<<<<<<< HEAD
	elif (q==4):
		v=None
=======
	# elif (q==4):
	# 	v=None
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	elif (q==5):
		if v!=None:
			print(v)
	elif (q==6):
		w,e=scan(int),scan(int)
		if v==None:
			print(1)
		else:
			if 0<=e<len(v):
				v[e]=w
				print(0)
			else:
				print(1)
	elif (q==7):
		e=scan(int)
		if v==None:
<<<<<<< HEAD
			print(w,1)
		else:
			if 0<=e<len(v):
				print(v[e],0)
			else:
				print(w,1)
=======
			print(1,w)
		else:
			if 0<=e<len(v):
				print(0,v[e])
			else:
				print(1,w)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	elif (q==8):
		w=scan(int)
		if v!=None:
			e=len(v)
<<<<<<< HEAD
			for t in range(e,w):
				v.append(t)
=======
			w=abs(w)
			for t in range(e,w):
				v.append(0)
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
			v=v[:w]
			print(0)
		else:
			e=0
			print(1+max(0,w-e))
	elif (q==9):
		if v!=None:
			w=len(v);
			print(w)
		else:
			w=0
			print(w)
	else:
		break;
