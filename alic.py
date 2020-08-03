llint a,s,d,e
scan(a,s)
d=s-2
e=1
while d>0:
 if d&1:
  e*=a
  e%=s
 a*=a
 a%=s
 d=d>>1
print (e)
