def lindex(q,e):
 for r,w in enumerate(q):
  if w==e:
   return r

def bindex(q,e):
 if len(q)==0:
  return
 if len(q)==1:
  if q[0]<e:
   return 1
  return 0
 c=len(q)//2
 if e<q[c]:
  return bindex(q[:c],e)
 return bindex(q[c:],e)+c

q=[1000+w*2 for w in range(100)]
print(bindex(q,999))
print(bindex(q,1000))
print(bindex(q,1001))
print(bindex(q,1002))
print(bindex(q,1003))
print(bindex(q,1004))
print(bindex(q,2000))
