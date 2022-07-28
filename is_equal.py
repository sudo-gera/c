from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
if len(set(a))>1:
	exit(1)
