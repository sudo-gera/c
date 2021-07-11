a=[1,2,3,4,5]
pse=2**3
psc=[0]*(pse*2)
def ibs(s,f):
	return (pse+s)//(f-s)
def psi(s=0,f=pse):
	if f-s==1:
		if s<len(a):
			psc[ibs(s,f)]=a[s]
		else:
			psc[ibs(s,f)]=0
	else:
		c=(f+s)//2
		psc[ibs(s,f)]=psi(s,c)+psi(c,f)
	return psc[ibs(s,f)]
psi()
def psum(s,f,ls=0,lf=pse):
	if s==ls and f==lf:
		return psc[ibs(s,f)]
	c=(ls+lf)//2
	if f<=c:
		return psum(s,f,ls,c)
	if s>=c:
		return psum(s,f,c,lf)
	return psum(s,c,ls,c)+psum(c,f,c,lf)
print(psum(0,5))
print(psum(1,4))
