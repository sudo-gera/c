import os,time,random
term=os.get_terminal_size
os.system('>key.a')
print('\n'*(term()[1]-2))
ls=0
q=5
a=5
f='d'
lf='d'
sn=[[5,w] for w in range(5,30)][::-1]
eq=random.randint(0,term()[1]*2-11)
ea=random.randint(0,term()[0]-1)
fc=list(range(30,38))+list(range(90,98))
bc=list(range(40,48))+list(range(100,108))
bd=[]
bdc=0
bdi=0
bdl=0
bdm=5
bdw=200
tab=8
fs=''
ma=0
aver=0
llen=0
ma=len(sn)
aver=len(sn)/1.0
llen=1
col=0
ons=[]
while 1:
 if col==1:
  print('\x1b['+str(random.choice(fc))+';'+str(random.choice(bc))+'m')
 if col==2:
  print('\x1b[5;'+str(random.choice(fc))+';'+str(random.choice(bc))+'m')
 print('\x1b[2j\x1b[H')
 ns=sn[:]
 ns+=[[ea,eq]]
 ns+=bd
 pns=[w for w in ns if w not in ons]
 mns=[w for w in ons if w not in ns]
 print('\x1b[33m')
 for w in pns:
  if w[1]%2:
   if [w[0],w[1]-1] in ns:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H█')
   else:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H▄')
  else:
   if [w[0],w[1]+1] in ns:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H█')
   else:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H▀')
 for w in mns:
  if w[1]%2:
   if [w[0],w[1]-1] in ns:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H▀')
   else:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H ')
  else:
   if [w[0],w[1]+1] in ns:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H▄')
   else:
    print('\x1b['+str(w[1]//2+1)+';'+str(w[0]+1)+'H ')
 ons=ns[:]
 print('\x1b[35m')
 print('\x1b['+str(term()[1]-3)+';0H'+'  '*term()[0])
 print('\x1b['+str(term()[1]-2)+';0H'+'now:',len(sn),'max:',ma,'aver:',aver)
 print('\x1b['+str(term()[1]-3)+';0H'+'█'*(bdl*term()[0]//bdw)+int(bool(max(bdl,0)))*chr(9615-max(bdl,0)*term()[0]*8//bdw%8))
 print('\x1b['+str(term()[1]-4)+';0H'+'═'*term()[0])
 if bdc==bdm:
  bdq=random.randint(1,term()[1]*2-12)
  bda=random.randint(1,term()[0]-2)
  bd+=[[bda-1,bdq-1]]
  bd+=[[bda+1,bdq-1]]
  bd+=[[bda-1,bdq+1]]
  bd+=[[bda+1,bdq+1]]
  bd+=[[bda+1,bdq]]
  bd+=[[bda-1,bdq]]
  bd+=[[bda,bdq+1]]
  bd+=[[bda,bdq-1]]
  bd+=[[bda,bdq]]
  bdc=bdm+1
  bdl=bdw
 elif bdc==0:
  bd=[]
 if bdl==0:
  bd=[]
  bdc=0
 bdl-=1
 nls=int(os.popen('ls -l key.a').read().split()[4])
 z=open('key.a')
 z.read(ls)
 fs+=z.read(nls-ls)
 z.close()
 ls=nls
 if fs=='\x1b[A':
  fs='w'
 if fs=='\x1b[B':
  fs='s'
 if fs=='\x1b[C':
  fs='d'
 if fs=='\x1b[D':
  fs='a'
 fs=''.join([fff for fff in fs if fff in 'asdwp'])
 if fs== '':
  fs=f
 if 1:
  f=fs[0]
  fs=fs[1:]
  if   f=='w':
   if lf == 's':
    q+=1
   else:
    q-=1
    lf=f
   q%=term()[1]*2-10
  elif f=='a':
   if lf == 'd':
    a+=1
   else:
    a-=1
    lf=f
   a%=term()[0]
  elif f=='s':
   if  lf == 'w':
    q-=1
   else:
    q+=1
    lf=f
   q%=term()[1]*2-10
  elif f=='d':
   if lf == 'a':
    a-=1
   else:
    a+=1
    lf=f
   a%=term()[0]
  elif f=='p':
   print('\x1b[0m')
   print('\x1b[0;0H'+' '*term()[0]*(term()[1]-2))
   print('\x1b[2j\x1b[0;0H',end='')
   exit()
 if [a,q] in sn:
  sn=sn[sn.index([a,q])+1:]
  ma=max(ma,len(sn)+bdi)
  aver=(aver*llen+len(sn))/(llen+1)
  llen+=1
 if ea==a and eq==q:
  bdc+=1
  eq=random.randint(0,term()[1]*2-11)
  ea=random.randint(0,term()[0]-1)
  sn=sn[:]+[[a,q]]
  ma=max(ma,len(sn)+bdi)
  aver=(aver*llen+len(sn))/(llen+1)
  llen+=1
 elif [a,q] in bd:
  bdi=15*bdl//bdw
  bdm=10*bdl//bdw+1
  bd=[]
  bdc=0
  bdl=0
  bdi-=1
  sn=sn[:]+[[a,q]]
  ma=max(ma,len(sn)+bdi)
  aver=(aver*llen+len(sn))/(llen+1)
  llen+=1
 elif bdi:
  bdi-=1
  sn=sn[:]+[[a,q]]
  ma=max(ma,len(sn)+bdi)
  aver=(aver*llen+len(sn))/(llen+1)
  llen+=1
 else:
  sn=sn[1:]+[[a,q]]
 #time.sleep(0.5)
