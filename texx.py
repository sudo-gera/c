q=0
mw=0
while 1:
 w=1
 while 1:
  s=sum(map(int,str(w+q)))
  if s%w:
   break
  w+=1
 if w>mw:
  mw=w
  print(q+1,w-1)
 q+=1
 if q%100000==0:
  print('--',q)
