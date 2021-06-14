def color(q,s=1):
	return ''.join(['\x1b['+str(int(w)+30 if int(w)<8 else int(w)-8+90  if int(w)==8 else int(w)-8+90-1+4)+'m'+(str(w) if s else chr(9608))+'\x1b[0m' for w in str(q)]) 
def pcolor(*q,**w):
	print(color(*q,**w))
from random import randint
from random import random
from time import time
from functools import reduce
###
ps=[436.0652, 11.88665, 242.0223, 8.410791, 11.16398, 31.4568, 10.14838, 14.5318, 12.35675, 11.1911]
### <<< 0 >>> <<< 1 >>> <<< 2 >>> <<< 3 >>> <<< 4 >>> <<< 5 >>> <<< 6 >>> <<< 7 >>> <<< 8 >>> <<< 9 >>>
def prand(a):
	s=random()*sum(a)
	q=0
	while s>0:
		s-=a[q]
		q+=1
	return q-1
def neint(q):
	try:
		return int(q)
	except:
		return -1
while 1:
	if ps[0]==0:
		q=prand([1]*10)
	else:
		q=prand(ps)
	r=reduce(lambda a,s:a*s,ps)
	if r>10**6:
		r=int(r)
	r=str(r)
	r=r[::-1]
	r=' '.join([''.join(r[w:w+3]) for w in range(0,len(r),3)])
	r=r[::-1]
	print(r)
	pcolor(q,s=0)
	t1=time()
	while q!=neint(input()):
		t1-=8
	t2=time()
	p=(t2-t1)**4
	cf=open(__file__).read()
	cf=cf.split('###')
	if ps[0]==0:
		p**=2
		p=float((str(p)[:8]+'1'*8)[:8])
		ps=[p]*10
	else:
		p=ps[q]*0.8+p*0.2
		p=float((str(p)[:8]+'1'*8)[:8])
		ps[q]=p
	cf[1]='\nps='+str(ps)+'\n'
	cf='###'.join(cf)
	open(__file__,'w').write(cf)