scan(int k,int n,int m,int b,int e)
struct nex:
 int n,w,h
new nex q[100000]
new int a[100000]
nex t
for w<m:
 scan(int p,int s,int r)
 if r<k:
  t.n=s
  t.w=r
  t.h=0
  push q[p][t]
  t.n=p
  t.w=r
  t.h=0
  push q[s][t]
int f[10000]
for w<10000:
 f[w]=0
scan(int l)
for w<l:
 scan(f[w])
new int i
for w<n:
 i.clear()
 for e in q[n]:
  push i[e]
 now=0
 while now<i.size():
  
