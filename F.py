from h import *
n=scan()
a=[[[0 for r in range(n)] for e in range(n)] for w in range(n)]
while 1:
	q=scan()
	if q==1:
		x,y,z,k=scan([int]*4)
		a[x][y][z]+=k
	if q==2:
		x1,y1,z1,x2,y2,z2=scan([int]*6)
		s=0
		for w in range(x1,x2+1):
			for e in range(y1,y2+1):
				for r in range(z1,z2+1):
					s+=a[w][e][r]
		print(s)
	if q==3:
		break




