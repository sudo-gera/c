o=open
from os import *
open=o
from random import *
from time import *
from multiprocessing import *


def run(p):
	p=str(int(time()*2**64))
	# p=''
	while 1:
		dd=randint(7,21)
		open('stdin.txt'+p,'w').write(
				str(dd)+'\n'+
				' '.join([
					str(randint(1,10**6)) for w in range(dd)
				])+'\n'
			)
		# q=str(run3([int(w) for w in open('stdin.txt'+p).read().split()][1:]))
		# a=str(run2([int(w) for w in open('stdin.txt'+p).read().split()][1:]))
		# q=popen('python3 test.py < stdin.txt'+p).read().strip()
		a=popen('./a.out < stdin.txt'+p).read().strip()
		q=popen('./b.out < stdin.txt'+p).read().strip()
		if q!=a:
			# print('differs ')
			print(open('stdin.txt'+p).read())
			# exit()

if __name__ == '__main__':
	Pool().map(run,range(16))