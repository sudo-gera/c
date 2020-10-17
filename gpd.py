from fractions import Fraction as f
a=[0]*12
a[0]=9
a[1]=1
a[2]=5
a[3]=1
a[4]=1
a[5]=1
a[6]=1
a[7]=1
a[8]=1
a[9]=5
a[10]=1
a[11]=18
en=1
ed=1
for w in range(1234,-1,-1):
	en,ed=ed+en*a[(w-1)%11+1 if w else w],en
q=f(en,ed)
b=(9+q)/4
c=(9-q)/4
def s(w):
	return pow(b,w)+pow(c,w)
#print(float(s(737)**2-s(736)*s(738)))
print(float(b*c))
print(float(b*b+c*c))
