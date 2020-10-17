l=1000
int a[l]
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
for 12=w<l:
	a[w]=a[w-11]
en=a[l-1]
ed=1
y=0
for l-2=y>-1:
	n=ed+a[y]*en
	d=en
	ed=d
	en=n
def int gcd(a,s):
	return s?gcd(s,a%s):a
g=gcd(ed,en)
ed/=g
en/=g
print()
printf("%Li/%Li\n",en,ed)