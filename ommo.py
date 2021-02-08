for x in range(201):
	for n in range(100):
		if x*n%100==0 and (x+1)*(n+1)%100==0 and 0<(x+1)*(n+1)//100-x*n//100<2:
			print(x,n)