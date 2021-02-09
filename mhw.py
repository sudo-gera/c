q=input()
from re import *
e=r'\s*'
v=r'[\-!-(:-~]\S*'
n=r'\d+'
if fullmatch(e+v+e+':='+e+v+e,q) or fullmatch(e+v+e+':='+e+n+e,q):
	print('YES')
else:
	print('NO')