c=[]
def run(q,w):
 global c
 for e in range(w):
  while 1:
   while len(c)==0:
    c+=input().split()
   r=c[0]
   c=c[1:]
   try:
   	r=int(r)
   except:
    print('cannot read:',r)
   else:
    break
  if len(q)>e:
   q[e]=r
  else:
   q.append(r)

q=[1,1,1]
run(q,6)
print(q)

