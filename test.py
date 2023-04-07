for q in range(60):
 for w in range(5):
  a=q*2
  s=q*3
  a-=w
  s-=4-w
  if a*4==s*3:
   print(a+w,s+4-w)

