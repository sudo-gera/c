exec(open('/home/gera/.pythonrc').read())
class mon:
 def __init__(s):
  s.d=dict()
  s.c=fraction(0)
 def norm(s):
  for w in list(s.d.keys()):
   if s.d[w]==0:
    del(s.d[w])
 def __mul__(s,o):
  e=dict()
  for w in list(s.d.keys())+list(o.d.keys()):
   e[w]=0
   if w in s.d.keys():
    e[w]+=s.d[w]
   if w in o.d.keys():
    e[w]+=o.d[w]
  r=mon()
  r.d=e
  r.c=s.c*o.c
  r.norm()
  return r
 def __eq__(s,o):
  s.norm()
  o.norm()
  if s.c!=o.c:
   return 2==3
  if list(s.d.keys())!=list(o.d.keys()):
   return 2==3
  for w in s.d.keys():
   if s.d[w]!=o.d[w]:
    return 2==3
  return 2==2
 def __str__(s):
  s.norm()
  e=str(s.c)
  if e[0]!='-':
   e='+'+e
  for w in sorted(list(s.d.keys())):
   e+='*'+str(w)+'^'+str(s.d[w])
  return e
class pol:
 def __init__(s):
  s.a=[]
 def norm(s):
  for w in s.a:
   w.norm()
  s.a=list(map(lambda d:[sorted(list(d.d.items())),d],s.a))
  a=[]
  s.a.sort(key=lambda d:d[0])
  for w in s.a:
   if a:
    if a[-1][0]==w[0]:
     a[-1][1].c+=w[1].c
    else:
     a+=[w]
   else:
    a+=[w]
  a=[w[1] for w in a if w[1].c]
  s.a=a
 def __add__(s,o):
  e=pol()
  e.a=s.a[:]+o.a[:]
  e.norm()
  return e
 def __sub__(s,o):
  e=pol()
  e.a=o.a[:]
  for w in range(len(e.a)):
   e.a[w].c*=-1
  e.a+=s.a[:]
  e.norm()
  return e
 def __mul__(s,o):
  e=pol()
  for w in s.a:
   for r in o.a:
    e.a+=[w*r]
  e.norm()
  return e
 def __eq__(s,o):
  s.norm()
  o.norm()
  if len(s.a)!=len(o.a):
   return 2==3
  return all([s.a[w]==o.a[w] for w in range(len(s.a))])
 def __str__(s):
  s.norm()
  e=''.join([str(w) for w in s.a])
  if e and e[0]=='+':
   e=e[1:]
  return e
class item():
 def __init__(s):
  s.p=pol()
  s.q=pol()
  s.q.a+=[mon()]
  s.q.a[0].c=fraction(1)
 def norm(s):
  s.p.norm()
  s.q.norm()
  if s.q==pol():
   s.p=pol()
  if s.p==pol():
   s.q=pol()
   s.q.a+=[mon()]
   s.q.a[0].c=fraction(1)
  if s.p==s.q:
   s.p=pol()
   s.p.a+=[mon()]
   s.p.a[0].c=fraction(1)
   s.q=pol()
   s.q.a+=[mon()]
   s.q.a[0].c=fraction(1)
  g=0
  for w in s.p.a:
   g=gcd(w.c.numerator,g)
  for w in s.q.a:
   g=gcd(w.c.numerator,g)
  for w in s.p.a:
   w.c/=g
  for w in s.q.a:
   w.c/=g
  g=1
  for w in s.p.a:
   g=w.c.denominator*g//gcd(w.c.denominator,g)
  for w in s.q.a:
   g=w.c.denominator*g//gcd(w.c.denominator,g)
  for w in s.p.a:
   w.c*=g
  for w in s.q.a:
   w.c*=g
  l=[]
  for w in s.p.a+s.q.a:
   l+=list(w.d.keys())
  l=set(list(l))
  '''
  for w in l:
   c=1/0.5**1030
   for e in s.p.a+s.q.a:
    if w in  e.d:
     c=min(e.d[w],c)
   for e in s.p.a:
    if w in e.d:
     e.d[w]-=c
   for e in s.q.a:
    if w in e.d:
     e.d[w]-=c
  '''
  s.p.norm()
  s.q.norm()
 def __add__(s,o):
  e=item()
  e.p=s.p*o.q+s.q*o.p
  e.q=s.q*o.q
  e.norm()
  return e
 def __sub__(s,o):
  e=item()
  e.p=s.p*o.q-s.q*o.p
  e.q=s.q*o.q
  e.norm()
  return e
 def __mul__(s,o):
  e=item()
  e.p=s.p*o.p
  e.q=s.q*o.q
  e.norm()
  return e
 def __truediv__(s,o):
  e=item()
  e.p=s.p*o.q
  e.q=s.q*o.p
  e.norm()
  return e
 def __eq__(s,o):
  s.norm()
  o.norm()
  return s.p==o.p and s.q==o.q
 def __str__(s):
  s.norm()
  return '('+str(s.p)+')/('+str(s.q)+')'
'''
a=[item(),item(),item()]
a[0].p.a+=[mon()]
a[0].p.a[0].c=fraction(1)
a[0].p.a[0].d={'x':1}
a[1].p.a+=[mon()]
a[1].p.a[0].c=fraction(1)
a[1].p.a[0].d={'y':1}
a[0].p.a+=[mon()]
a[0].p.a[0].c=fraction(1213)
a[1].p.a+=[mon()]
a[1].p.a[0].c=fraction(1741)
a[2].p.a+=[mon()]
a[2].p.a[0].c=fraction(2161)
'''
f=fraction(1)
a=[2473*f,2477*f,2503*f]
a=list(map(int,'1601	1607	1609'.split()))
a[0]*=f
a[1]*=f
a[2]*=f
wi=0
def black(a,s):
 try:
  return (a-s)/a
 except:
  return 0
fr=dict()
while fraction(a[0]+a[1]) not in a:
 for w in range(wi+1):
  for (s,d) in [(a[w],a[wi]),(a[wi],a[w])]:
   f=black(s,d)
   if f not in a:
#    print(len(a),str(f)+'=black('+str(s)+','+str(d)+')')
#    print(len(a),f)
    fr[str(f)]=[str(s),str(d)]
    a+=[f]
 wi+=1

seq=[str(a[-1])]
print(*list(enumerate(a)),sep='\n')
bas=[str(w) for w in a[:3]]
while seq:
 f=seq[0]
 s,d=fr[f]
 print(f,s,d)
 if s not in bas:
  seq+=[s]
 if d not in bas:
  seq+=[d]
 seq=seq[1:]
