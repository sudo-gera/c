q=0
while 1:
 q+=1
 for w in range(int(q**0.5)):
  e=int((q-w*w)**0.5)
 if q*q+e*e==q:
  print(q,w,e)
