task=1
if task==1:
	from bisect import insort
	n=int(input())
	d=[[-1,-1] for w in range(80)]
	for w in range(n):
		r=int(input())
		insort(d[r%80],r)
		d[r%80]=d[r%80][1:]
	d.sort(key=sum)
	d=d[-1]
	if -1 in d:
		print(0,0)
	else:
		print(*d)
if task==2:
	n=int(input())
	d=[0,0,0,0]
	for w in range(n):
		r=int(input())
		if r%62==0:
			d[0]+=1
		elif r%31==0:
			d[1]+=1
		elif r%2==0:
			d[2]+=1
		else:
			d[3]+=1
	print(d[0]*sum(d)+d[1]*d[2])
if task==3:
	n=int(input())
	im=0
	dm=0
	for w in range(n):
		x,y=list(map(int,input().split()))
		if x==y:
			im=max(im,abs(x))
		if x==-y:
			dm=max(dm,abs(x))
	if im*dm:
		print(im*dm)
	else:
		print('Треугольник не существует')
if task==4:
	from bisect import insort
	n=int(input())
	om=[[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1]]
	em=[[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1],[-1,-1]]
	for w in range(n):
		r=int(input())
		if r%2:
			insort(om,[r,w])
			om=om[1:]
		else:
			insort(em,[r,w])
			em=em[1:]
	m=0
	for w in om:
		for e in em:
			if w[0]>-1 and e[0]>-1 and abs(w[1]-e[1])>=6:
				m=max(m,w[0]+e[0])
	print(m)
if task==5:
	n=int(input())
	for w in range(n):
		if int(input())>0:
			print(w+1)
