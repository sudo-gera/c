from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

# a='qwertyuioplkjhgfdsazxcvbnm'
# a=list(a)
# shuffle(a)
# a=''.join(a)
# print(a)

n=1+2*rand(4)
print(n)
for w in range(n):
	# print(''.join([choice(a) for e in range(rand(1,11))]))
	print(rand(9),end=' ')
print()
# for w in range(n):
# 	# print(''.join([choice(a) for e in range(rand(1,11))]))
# 	print(rand(9999),end=' ')
# for w in range(n):
# 	# print(''.join([choice(a) for e in range(rand(1,11))]))
# 	print(rand(9999),end=' ')

# for w in range(n):
# 	print(choice('.X'),end='')
# print()
# print(rand(2*10**5))
