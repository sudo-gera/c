from os.path import *
from subprocess import *
from time import *
from sys import *
sleep(4)
p=expanduser('~/ubuntux/.subl_open')
while exists(p):
	f=list(open(p).read().splitlines())
	print(f)
	open(p,'w')
	for w in f:
		w=w.replace('/home/gera/','~/ubuntux/')
		Popen(['/opt/local/bin/subl',w])
	sleep(1)

