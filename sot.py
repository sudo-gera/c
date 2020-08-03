from time import asctime
c=1
e=1
for q in range(1114112):
 try:
  s=chr(q)
 except:
  if c:
   print(asctime(),q,'c=0')
   c=0
 finally:
  if c==0:
   print(asctime(),q,'c=1')
   c=1
  try:
   s.encode()
  except:
   if e:
    print(asctime(),q,'e=0')
    e=0
  finally:
   if e==0:
    print(asctime(),q,'e=1')
    e=1

