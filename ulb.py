h=[]
from urllib.error import HTTPError as E
from urllib.request import urlopen as u
def scan(q):
 global h
 if q in h:
  return
 h+=[q]
 f=q
 try:
  q=u(q).read().decode()
 except E:
  return
 if 'устав' in q.lower():
  print(f)
 q=q.replace('<','\x01\x02').replace('>','\x01')
 q=q.split('\x01')
 q=[w for w in q if w and w[0]=='\x02']
 q=[w.split() for w in q]
 q=[[e.split('=')[1] for e in w if '=' in e] for w in q]
 q=['\x01'.join(w) for w in q]
 q='\x01'.join(q)
 q=q.split('\x01')
 q=[w[1:] if w and w[0] in '"\'' else w for w in q]
 q=[w[:-1] if w and w[-1] in '"\'' else w for w in q]
 q=[[w] for w in q if w]
 for w in q:
  if w[0][0]=='/':
   w[0]='http://kpml.ru'+w[0]
  elif w[0][:7]!='http://' and w[0][:8]!='https://':
   if f[-1]=='/':
    w[0]=f+w[0]
   else:
    w[0]=f+'/'+w[0]
 for w in q:
  scan(w[0])
scan('http://kpml.ru/')
