def bp(q):
 s=''
 while q:
  s+=str(q%2)
  q//=2
 print(s[::-1])
for w in range(3,100):
 q=w*2+1
 q=q*q-5
 while q%2==0:
  q//=2
 bp(w*2+1)
 bp(q)
