aimport
name std
struct frag:
 lint beg,end
scan(int n,int m)
def comp(a,b):
 if a.end-a.beg>b.end-b.beg:
  return 1
 if a.end-a.beg<b.end-b.beg:
  return 0
 if a.beg<b.beg
  return 1
 return 0
set <frag,decltype(&comp)> mem (comp)
def bcomp(a,b):
 if a.beg<b.beg:
  return 1
 if a.beg>b.beg:
  return 0
 return a.end<b.end
set <frag,decltype(&bcomp)> bmem (bcomp)
def dcomp(a,b):
 if a.end<b.end:
  return 1
 if a.end>b.end:
  return 0
 return a.beg<b.beg
set <frag,decltype(&dcomp)> dmem (dcomp)
frag t,y,u,i,o
t.beg=0
t.end=n
mem.insert(t)
bmem.insert(t)
dmem.insert(t)
t.beg=-1
t.end=-1
vector <frag> his(m,t)
for w<m:
 scan(int q)
 if q>0:
  if mem.size()>0:
   t=*mem.begin()
   if t.end-t.beg>=q:
    print(t.beg)
    mem.erase(t)
    bmem.erase(t)
    dmem.erase(t)
    y.beg=t.beg
    y.end=t.beg+q
    his[w]=y
    if t.end-t.beg>q:
     t.beg-=q
     set.insert(t)
   else:
    print(0-1)
  else:
   print(0-1)
 else:
  q=-q-1
  if his[q].beg>-1:
   t=his[q]
   y.beg=t.end
   y.end=t.end
   auto p=bmem.upper_bound(y)
   


   if p!=bmem.end():
    u.end=p->beg
   else:
    u.end=-1
   y.end=t.beg
   p=dmem.find(y)
   if p!=dmem.end():
    u.beg=p->end
   else:
    u.beg=-1
   if u.end==-1 and u.beg == -1:
    mem.insert(t)
    bmem.insert(t)
    dmem.insert(t)
   elif u.end==-1:
    u.end=p.beg
    p=fin
   t.beg=-1
   t.end=-1
   his[q]=t
