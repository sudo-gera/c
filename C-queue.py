from h import *
v=Queue()
while 1:
	q,w,e,r=0,0,0,0
	ww=0
	q=scan(int)
	print('-',q)
	if (q==0):
		v=Queue()
	elif (q==1):
		w=scan()
		v.put(w)
		print(0);
	elif (q==2):
		if v.empty():
			print(1,0)
		else:
			w=v.get()
			print(0,w);
	elif (q==3):
		r=v.empty()+0;
		print(r)
	elif (q==4):
		a=[v.get() for w in range(v.qsize())]
		print(a)
		[v.put(w) for w in a]
	else:
		break;
