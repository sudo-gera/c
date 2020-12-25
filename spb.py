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