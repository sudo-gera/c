from os.path import *
from subprocess import *
from time import *
from sys import *
sleep(4)
p=expanduser('~/ubuntux/.subl_open')
while exists(p):
	a=open(p)
	f=a.read()
	print(f)
	a.close()
	del(a)
	# f=f.splitlines()
	open(p,'w').close()
	# for w in f:
	# 	w=w.replace('/home/gera/','~/ubuntux/')
	# 	Popen(['/opt/local/bin/subl',w])
	sleep(1)

