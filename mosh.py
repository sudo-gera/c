from random import shuffle
from multiprocessing import Pool
c=0
s=0
n=0
def run(*u):
	a=list(range(1,16))
	shuffle(a)
	a=[sum(a[w*3:w*3+3]) for w in range(5)]
	m=min(a)+max(a)
	return m
while 1:
	for m in Pool().map(run,range(12000000)):
		s=(s*n+m)/(n+1)
		n+=1
	print(s)