cimport math
scan(gint p, gint f)
scan(gdouble y)
def get(x):
 return sqrt(x*x+(1-y)*(1-y))/p+sqrt((1-x)*(1-x)+y*y)/f
double z,x,c,v,s,d
z=0
v=1
for w<1000:
 x=z+(v-z)/3
 c=v-(v-z)/3
 s=get(x)
 d=get(c)
 if s>d:
  z=x
 if s<d:
  v=c
 if s==d:
  z=x
  v=c
print(z`.64lf)

#(p*p*(1-2x+x*x)*((x*x+(1-y)*(1-y))))=(((x*x)*((1-x)*(1-x)+y*y))*(f*f))
