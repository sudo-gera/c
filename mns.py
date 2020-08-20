#import bits/stdc++.h
import vector
std::vector<int>a
for 1=k<12:
 ni=0+a.size()
 a.push_back(k)
 b=1
 while b:
  b=0
  for w<0+a.size():
   for e<w:
    for r<e:
     if a[e]*2==a[w]+a[r]:
      b=1
  if b:
   if ni:
    std::swap(a[ni],a[ni-1])
    ni--
   else:
    print('-----',k)
 for w<0+a.size():
  print(0+a[w],format=''=' ')
 print()
