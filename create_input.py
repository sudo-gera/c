from random import *
from fractions import Fraction
def rand(q=2**64):
	assert q
	return randint(0,q-1)

from h import *
for w in range(9):
	n=rand(2**15)+1
	for w in range(n):
		print(to_radix(rand(16),16),end='')
	print()
	n=rand(2**15)+1
	for w in range(n):
		print(to_radix(rand(16),16),end='')
	print()
