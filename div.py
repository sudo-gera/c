from math import gcd
q=int(input())
m=q
r=int(q**0.5+1)
for a in range(1,r):
 if q%a==0:
  b=q//a
  if b*a/gcd(a,b)==q:
   m=min(m,b)
print(m,q//m)
