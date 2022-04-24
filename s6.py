def get(n):
	return(sum([n%w for w in range(1,n)]))

for w in range(100):
	print(w,get(w)//20*'-')
