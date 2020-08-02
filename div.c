def gcd(a,b):
 if a<b:
  t=a
  a=b
  b=t
 while b:
  a=a%b
  t=a
  a=b
  b=t
 return a
def root(q):
 b=0L
 e=q
 while e-b>1:
  c=(b+e)/2
  d=c*c
  if d>q:
   e=c
  if d<q:
   b=c
  if d==q:
   b=c
   e=c
 return e
scan(lint q)
m=q
r=0L+root(q)
for 1=a<r:
 if q%a==0:
  b=q/a
  if b*a/gcd(a,b)==q:
   m=m<b?m:b
print(m,q/m)
