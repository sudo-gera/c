from os.path import *
from subprocess import *
from time import *
from sys import *
while exists(expanduser('~/ubuntux/.subl_open')):
	for w in open(expanduser('~/ubuntux/.subl_open')).read().splitlines():
		w=w.replace('/home/gera/','~/ubuntux/')
		Popen(['/opt/local/bin/subl',w])
	open(expanduser('~/ubuntux/.subl_open'),'w')
	sleep(1)

