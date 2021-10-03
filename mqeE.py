s=input()
p=input()
from re import *
if fullmatch(p,s):
	print('YES')
else:
	print('NO')