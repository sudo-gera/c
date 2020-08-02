ext=dict()
def ti(a):
 s=int(a+0.5)
 return s if abs(a-s)<0.001 else -1
def j(a,s=0):
# if s==0:
#  for w in range(2**len(a)):
#   s=[e if w&(1<<r) else '(-('+e+'))' for r,e in enumerate(a)]
#   j(s,1)
#  return
 if len(a)==1:
  aa=a[0]
  try:
   ext[ti(eval(aa))]=aa
  except:
   pass
  return
 for w in range(1,len(a)):
  s=a[:w-1]+['('+a[w-1]+'/'+a[w]+')']+a[w+1:]
  j(s)
  s=a[:w-1]+['('+a[w-1]+'*'+a[w]+')']+a[w+1:]
  j(s)
#  s=a[:w-1]+['('+a[w-1]+'-'+a[w]+')']+a[w+1:]
#  j(s)
  s=a[:w-1]+['('+a[w-1]+'+'+a[w]+')']+a[w+1:]
  j(s)
ext[-1]='0'
d=list('123456')
for w in range(64):
 print('-'*64,end='\r')
 print(chr(9608)*w,end='\r')
 s=[e if w&(1<<r) else '(-'+e+')' for r,e in enumerate(d)]
 j(s)
j(d)
d=dict()
for w in range(100):
 d[w+1]=''
for w in ext:
 d[w]=ext[w]
print(' '*64)
for w in d:
 print(w,'=',d[w])
