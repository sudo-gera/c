c=1
def run(n):
	if n==0:
		return
	global res
	res+=[0]*c
	run(n//3)
	run(2*n//3)
for w in range(40,80):
	res=[]
	run(w)
	from math import log
	print(log(len(res),w))
