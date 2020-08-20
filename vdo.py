import algorithm
name std
scan(int n,int k)
int a[200000]
for w<n+k:
 scan(int t)
 a[w]=t
struct dot:
 int x,y,g
dot y[200000]
u=0
for r<k+1:
 for t<k+1:
  dot i
  i.x=n+k-1-r
  i.y=t
  i.g=0
  y[u++]=i
pass
 int d[200000]
 for w<n+k-1:
  d[w]=a[w+1]-a[w]
 sort(d,d+n+k-1)
 d[n+k-1]=-1
 s=0
 m=-1
 v=-1
 for w<n+k-1:
  if d[w+1]-d[w]:
   if w+1-s>m:
    m=w+1-s
    v=d[w]
   s=w+1
 for w<u:
  if a[y[w].x+1]-a[y[w].x]==v and a[y[w].y+1]-a[y[w].y]==v or a[y[w].x-1]-a[y[w].x]==-v and a[y[w].y-1]-a[y[w].y]==-v:
   y[w].g=1
sort(y,y+u,[](dot a,dot b){return a.g;})
pass
 int e[200000]
 for w<200000:
  e[w]=-2
 for j<u:
  d=y[j]
  dx=0+d.x
  dy=0+d.y
  print(dx,dy)
  print(d)
  r=n+k-1-y[j].x
  t=0+y[j].y
  s=a[t]+a[n+k-1-r]
  int x=n+k-1-r
  int y=t
  l=0
  while l<n and x>t and y<n+k-1-r:
   if a[x]+a[y]==s:
    e[l++]=x--
    e[l++]=y++
   elif a[x]+a[y]<s:
    y++
   elif a[x]+a[y]>s:
    x--
  if l>=n/2:
   sort(e,e+n)
   for w<n:
    p=a[e[w]]
    print(p,end=' ')
   print()
   return 0
