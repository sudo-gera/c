q=1
while 1:
 q+=1
 a=list(set([w*w%q for w in range(q)]))
 s=list(set([w*w*w%q for w in range(q)]))
 t=[]
 for w in a:
  for e in s:
   t+=[(w+e)%q]
 t=list(set(t))
 t.sort()
 if t!=list(range(q)):
  print(q)
