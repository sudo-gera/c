compile:
 g++ {}
cimport math
int y=1024
bool t[y][y]
float f
%*f=y/2-0.5;*%
for w<y:
 for e<y:
  if sqrt((w-f)*(w-f)+(e-f)*(e-f))<=f:
   t[w][e]=1
  else:
   t[w][e]=0
for w<y:
 for e<y:
  if t[w][e]:
   print('_',end='')
   if e+1<y and t[w][e+1]:
    print('-',end='')
   else:
    print(' ',end='')
  else:
   print('  ',end='')
 print()
