from os.path import *
from subprocess import *
from time import *
from sys import *
a=open(expanuser('~/.subl_open'),'a')
for w in argv[1:]:
	w=abspath(w)
	a.write(w+'\n')
