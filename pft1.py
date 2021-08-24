n=int(input())
a=[[int(w) for w in input().split()] for q in range(n)]
s=[w for w in zip(a,a[1:])][1:]
q=a[0]
def sot(q,w,e,r,t,y):
	z,x,c,v=e-q,r-w,t-q,y-w
	return abs(z*c-x*v)
s=[5*sot(*q,*w[0],*w[1]) for w in s]
s=sum(s)
s=str(s)
s=s[:-1]+'.'+s[-1:]
print(s)