from os.path import *
from subprocess import *
from time import *
from sys import *
sleep(4)
while exists(expanduser('~/ubuntux/.subl_open')):
	f=open(expanduser('~/ubuntux/.subl_open')).read().splitlines()
	open(expanduser('~/ubuntux/.subl_open'),'w')
	for w in f:
		w=w.replace('/home/gera/','~/ubuntux/')
		Popen(['/opt/local/bin/subl',w])
	sleep(1)

