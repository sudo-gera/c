from math import *
def makesum(d1,d2):
	ff=lambda x:d1[0]*cos(x+d1[1])+d2[0]*cos(x+d2[1])
	j=16
	k=4
	aa=([[ff(w/j),w/j] for w in range(int(j*pi*4))])
	s=max([[sum([t[0] for t in aa[w:w+k]]),w] for w in range(len(aa))])[1]
	aa=aa[s:s+k]
	fi,st=aa[0][1],aa[-1][1]
	l=64
	for t in range(l):
		cl=(st+st+fi)/3
		cr=(st+fi+fi)/3
		if ff(cl) < ff(cr):
			st=cl
		if ff(cl) > ff(cr):
			fi=cr
		if ff(cl) ==ff(cr):
			st=cl
			fi=cr
	res=(fi+st)/2
	res=res%(pi*2)
	return [ff(cl),2*pi-res]

print(makesum([1,1],[8,-1.5707963267949]))