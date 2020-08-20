cint a=1<<19
int s[a]
int f[a]
scan(int d)
for w<d:
 scan(s[w])
auto m=-1L+1L<<31L
int o=-m
for w<d:
 m=m>s[w]?s[w]:m
for w<d:
 s[w]-=m
for w<d:
 o=o<s[w]?s[w]:o
for w<o:
 f[w]=0
for w<d:
 f[s[w]]++
e=0
w=0
for i<d+o:
 if f[e]==0:
  e++
 else:
  f[e]--
  s[w]=e
  w++
for w<d:
 s[w]+=m
for w<d:
 print(s[w])
