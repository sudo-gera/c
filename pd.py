'''
def base_cmp(q):
	if q*q>97:
		return 1
	if q*q==97:
		return 0
	if q*q<97:
		return -1

def gf(a):
	e=f(a[-1])
	for w in a[:-1][::-1]:
		e=1/e+w
	return e

def cmp(q):
	global a
	return base_cmp(gf(a+[q]))
'''
from fractions import Fraction as f
a=[0]*12
a[0]=9
a[1]=1
a[2]=5
a[3]=1
a[4]=1
a[5]=1
a[6]=1
a[7]=1
a[8]=1
a[9]=5
a[10]=1
a[11]=18

'''
for w in range(300):
	q=f(1)
	if len(a)%2:
		while cmp(q)==1:
			q+=1
		while cmp(q)==-1:
			q-=1
	else:
		while cmp(q)==-1:
			q+=1
		while cmp(q)==1:
			q-=1
	a.append(q)
'''

e=f(a[-1])
for w in range(64,-1,-1):
	e=1/e+a[(w-1)%11+1 if w else w]
print(e)