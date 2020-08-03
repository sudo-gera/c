def int gcd(int a,int b):
 return b?gcd(b,a%b):a
for w<7:
 for e<7:
  r=gcd(w,e)
  print(w,e,r)

