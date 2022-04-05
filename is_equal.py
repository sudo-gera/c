from sys import *
from json import *
a=loads(stdin.read())
a=[w.strip() for w in a]
p=a[0]
a=a[1:]
a=[[e for e in range(len(p)) if p[e:].startswith(w)] for w in a]
a=[len(w)>1 for w in a]
a=all(a)
if not a:
	exit(1)
