from h import *
p=scan()
q=scan()
g=gcd(p,q)
p//=g
q//=g
a=[]
while (1):
b=0
e=18446744073709551616
ic(b,e,len(a))
while (b+1<e):
c=(b+e)//2
append(a,c)
rp=0
rq=1
w=len(a)-1
while (w>-1):
rp+=rq*a[w]
rq*=w+2
g=gcd(rp,rq)
rp//=g
rq//=g
w-=1
if (rp*q>rq*p):
e=c
if (rp*q<rq*p):
b=c
if (rp*q==rq*p):
print(*a)
exit(0)
pop(a)
append(a,b)
