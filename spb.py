<<<<<<< HEAD
from math import factorial
def c(n,k):
	if n>=0 and k>=0 and n-k>=0:
		return factorial(n)//factorial(k)//factorial(n-k)
	else:
		return 0
for n in range(300):
	e=0
	for k in range(2,n+1):
		e+=c(n,2)/c(k,2)
	if (n-1)**2<e:
		print(n,(n-1)**2,e)
=======
from sys import *
task=int(argv[1])
if task==1:
	from math import *
	def c(n,k):
		return factorial(n)//factorial(k)//factorial(n-k)
	for w in range(4,8):
		print('c('+str(w)+',2)='+str(c(w,2))+'>'+str(c(w,4))+'=c('+str(w)+',4)')
if task==2:
	for w in range(100,1000):
		if str(w)==str(w+594)[::-1]:
			e=str(w)
			print(f'пусть a={e[0]}, b={e[1]}, c={e[2]} тогда 100*{e[0]}+10*{e[1]}+{e[2]}+594=100*{e[2]}+10*{e[1]}+{e[0]}')
>>>>>>> 4072415f2c759ddb6f38bcbb1e537d3d95ae55e7
