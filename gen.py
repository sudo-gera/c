a=open('gen','w')
a.write('100000000 ')
from random import randint
for w in range(10**8):
 if w%10**5==0:
  print(w//10**5)
 a.write(str(randint(0,10**8))+' ')
a.close()
