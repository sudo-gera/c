from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

n=rand(20)
print(n)
for w in range(n):
	a=rand(4)
	print('ADD DELETE EDITPHONE PRINT'.split()[a])
	if a==0:
		print(chr(ord('a')+rand(4)),rand(20))
	if a==1:
		print(chr(ord('a')+rand(4)))
	if a==2:
		print(chr(ord('a')+rand(4)),rand(20))
	if a==3:
		print(chr(ord('a')+rand(4)))

