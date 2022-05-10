from random import *
from fractions import Fraction
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)

n=rand(1,999)
m=rand(1,n+1)
f=[]
while len(f)<m:
	f.append('')
	for w in range(rand(1,41)):
		f[-1]+=choice('qwertyuioplkjhgfdsazxcvbnm')
a=[
	[choice(f),rand(999)]
for w in range(n)]
m=len(set([w[0] for w in a]))
print(m,n)
for w in a:
	print(*w)
