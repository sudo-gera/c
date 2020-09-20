cimport stdlib
gint l=100000000
gint a[100000000]
cimport stdlib
struct _f:
	int n,d
def int gcd(int a,int s):
	return s?gcd(s,a%s):a
def norm(_f a):
	g=gcd(a.n,a.d)
	a.n/=g
	a.d/=g
	if a.d<0:
		a.n*=-1
		a.d*=-1
	return a
def __add__(_f a,_f s):
	_f d
	d.n=a.n*s.d+s.n*a.d
	d.d=a.d*s.d
	d=norm(d)
	return d
def __sub__(_f a,_f s):
	_f d
	d.n=a.n*s.d-s.n*a.d
	d.d=a.d*s.d
	d=norm(d)
	return d
def __mul__(_f a,_f s):
	_f d
	d.n=a.n*s.n
	d.d=a.d*s.d
	d=norm(d)
	return d
def __div__(_f a,_f s):
	_f d
	d.n=a.n*s.d
	d.d=a.d*s.n
	d=norm(d)
	return d
def f(int q):
	_f d
	d.n=q
	d.d=1
	return d
def __lt__(_f a,_f s):
	return a.n*s.d<a.d*s.n
def __gt__(_f a,_f s):
	return a.n*s.d>a.d*s.n
def __eq__(_f a,_f s):
	return a.n*s.d==a.d*s.n
def base_cmp(_f q):
	if q*q>f(97):
		return 1
	if q*q==f(97):
		return 0
	if q*q<f(97):
		return -1
def gf():
	e=f(a[l-1])
	y=0
	for l-2=y>-1:
		e=f(1)/e+f(a[y])
	return e
def cmp(int q):
	a[l++]=q
	c=base_cmp(gf())
    l--
    return c
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
g=gf()
int n=g.n
int d=g.d
print(n,'/',d,sep='')