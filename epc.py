t=0
for x<2011:
 for y<2011:
  for s<3:
   z=2011*s-x-y
   if z>=0  and z<2011 and (x*y+y*z+z*x)%2011==0:
    t++
print (t)
