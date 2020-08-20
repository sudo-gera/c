g=dict()
def win(z,x,c,p=0,r=1):
 q=[z,x,c]
 f=chr(q[0])+chr(q[1])+chr(q[2])+chr(p)
 if f in g:
  return g[f]
 if max(q)<1:
  return 1.5
 if sum(q)==2:
  if (q[1]-q[2])%3:
   return 2
  return 1
 s=[0,0,0]
 for w in range(3):
  if q[w]:
   q[w]-=1
   s[w]=win(*q,1-p,0)
   q[w]+=1
 if p:
  d=max(s)
 else:
  s=[w if w else 9 for w in s]
  d=min(s)
 g[f]=d
 if r:
  return [d,s]
 return d


from sys import argv
argv=list(map(int,argv[1:]))
print(win(*argv))

exit()

for w in range(100):
 e=[w//3,(w+2)//3,(w+1)//3]
 print(e,win(*e))

exit()
for w in range(16):
 for e in range(16):
  for r in range(16):
#   print(['  ','\x1b[105m  \x1b[0m','  ','\x1b[103m  \x1b[0m'][win(w,e,r)],end='')
   print(win(w,e,r),end='\t')
  print()
 print()
