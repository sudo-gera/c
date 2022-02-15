from h import *

def aout(q):
	return int(popen('./a.out '+str(q)).read())

if len(argv)>1:
	print(fibonacci(int(argv[1])))
	exit()
q=0
while 1:
	q+=1
	if aout(q)!=fibonacci(q):
		print(q)
		break
