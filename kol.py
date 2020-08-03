q=32
d=1<<q
def ss(k):
 return  -28+128*((((((((k*4+1)*16-1)*4-1)*4+2)*4+2)*16+1)*4-1)*16-1)
while 1:
 k=1
 s=ss(k)
 while pow(51,s,d)!=17:
  k+=1
  s=ss(k)
 print(q,k)
 b=''
 print(s)
 while s:
  b+=str(s%4)
  s//=4
 print(b)
 q+=1
 d*=2
