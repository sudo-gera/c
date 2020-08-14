#debug:
# recursionshow=0
limport mmd
scan(int n)
global:
 cint q=524288
# cint q=8
 int a[q]
 int s[q*2]
for w<q:
 a[w]=0
for w<n:
 scan(a[w])
def int init(beg,end):
 cen=(end+beg)/2
 e=beg
 if end-beg>1:
  z=init(beg,cen)
  x=init(cen,end)
  e=z
  if a[z]>a[x]:
   e=x
 d=(q+beg)/(end-beg)
 s[d]=e
 return e
init(0,q)
def int mmf(int beg,int end,int sb=0,int se=q):
 sc=(se+sb)/2
 if beg==sb and end==se:
  return s[(q+beg)/(end-beg)]
 if end<=sc:
  return mmf(beg,end,sb,sc)
 if sc<=beg:
  return mmf(beg,end,sc,se)
 z=mmf(beg,sc,sb,sc)
 x=mmf(sc,end,sc,se)
 if a[z]>a[x]:
  return x
 return z
def int key(int beg,int end):
 if end-beg==0:
  return 0LL
 sep=mmf(beg,end)
 return max(key(beg,sep)+(end-sep)*a[sep],key(sep+1,end)+a[sep]*(sep-beg+1))
print(key(0,n)`Li)
