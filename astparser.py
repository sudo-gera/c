from sys import argv
from functools import reduce
from re import *
from pprint import pprint
from ast import *
def error(l,q):
	print('\x1b[31m[error line '+str(l)+']\x1b[0m',q)
	exit(1)
def lprint(q):
	print('lprint',q)
	return q
if len(argv)>1:
	filename=argv[1]
	text=open(filename).read()
else:
	from sys import stdin
	text=stdin.read()

# body=parse(text).body
# print(*[dump(w,indent=4) for w in body],sep='\n')

par=parse(text)
print(dump(par,indent=4))


