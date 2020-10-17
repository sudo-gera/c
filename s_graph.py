import algorithm
name std
scan(int n,int m)
struct rc:
 int b,e
int v[1001]
rc r[1000]
vl=0
rl=0
for w<m:
 rc t
 print(w,m)
 scan(int b,int e)
 t.b=b
 t.e=e
 r[rl++]=t
def int cmp(rc a,rc s):
 return a.b<s.b
sort(r,r+rl,cmp)
for w<rl:
 while r[w].b>rl:
  v[++vl]=w
v[++vl]=w
q=0
print('u')
if 0:
 while q>-1:
  scan(q)
  for v[q]=w<v[q+1]:
   s=0+r[w].e
   print(s,end=' ')
 print()


