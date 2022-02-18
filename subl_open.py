from os.path import *
from subprocess import *
from time import *
from sys import *
while exists(expanduser('~/ubuntu/.subl_open')):
	for w in open(expanduser('~/ubuntu/.subl_open')).read().splitlines():
		w=w.replace('/home/gera/','~/ubuntu/')
		Popen(['/opt/local/bin/subl',w])
	open(expanduser('~/ubuntu/.subl_open'),'w')
	sleep(1)

