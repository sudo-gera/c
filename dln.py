int a,s,d,e
scan(a,s,d)
e=1
a%=d
while s>0:
 if s%2:
  e*=a
  e%=d
 s/=2
 a*=a
 a%=d
print(e)
