def d(a,s):
	return a%s==0
for a in range(1,91):
	if all([d(90,a) and (  d(x,a) or ( not d(x,15) or not d(x,20) ) ) for x in range(1,1000000)]):
		print(a)