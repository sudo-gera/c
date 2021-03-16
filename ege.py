def run(z):
	for x in range(101):
		q=z*(z+x)
		if 1000000<=q<2000001:
			c=0
			r=int(q**0.5)
			while 1:
				if q%r==0 and abs(q//r-r)<=100:
					#print(q,r,q//r)
					c+=1
				if c>=3:
					break
				if q-r*r>100*r:
					break
				r-=1
			if c==3:
				print(q)

if __name__ == '__main__':
	if 0:

		from multiprocessing import Process
		from functools import partial
		for w in range(1000,2001):
			Process(target=partial(run,w)).start()
	else:
		for w in range(1000,2001):
			run(w)