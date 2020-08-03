int q,w,e
scan(q)
while q%2==0:
 print('2')
 q>>=1
w=3
while w*w<=q:
 while q%w==0:
  print(w)
  q/=w
 w+=2
if q!=1:
 print(q)
