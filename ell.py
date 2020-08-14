r='=-0987654321ё\\ъхзщшгнекуцйэждлорпавыф.юбьтимсчяЁ!@#$%^&*()_+ЙЦУКЕНГШЩЗХЪ/ФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,'
t='=-0987654321`\\][poiuytrewq\';lkjhgfdsa/.,mnbvcxz~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:"ZXCVBNM<>?'
from random import choice,randint,shuffle
while 1:
 q=[r,t]
 shuffle(q)
 q,w=q
 a=randint(0,len(t)-1)
 print(w[a])
 e=[choice([e for e in q if e != q[a]]) for w in range(9)]+[q[a]]
 shuffle(e)
 print(' '.join(e))
 print(' '.join(map(str,range(len(e)))))
 s=0
 while s!=q[a]:
  try:
   s=e[int(input())]
  except:
   s=0
