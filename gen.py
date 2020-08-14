from random import randint
from os import popen
from time import time
l=m=0
while 1:
 t=[str(randint(-2**17,2**17)) for w in range(randint(0,2**19))]
 open('in','w').write(str(len(t))+'\n'+'\n'.join(t))
 y=time()
 a=popen('./a.out<in').read().split()
 u=time()
 b=popen('./b.out<in').read().split()
 i=time()
 if a!=b:
  print(-1)
  exit()
 else:
  k=(u-i)/(y-u)
  l=(l*m+k)/(m+1)
  m+=1
  print(l)
