def run(z):
	for x in range(101):
		q=z*(z+x)
		if 1000000<=q<2000001:
			c=0
			r=int(q**0.5)
			while 1:
				if q%r==0 and q//r-r<=100:
					c+=1
				if c>=3:
					break
				if q-r*r>100*r:
					break
			if c==3:
				print(q)

from multiprocessing import Pool
Pool().map(run,range(1000,1001))
