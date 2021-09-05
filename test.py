try:
	from icecream import ic
	ic.configureOutput(includeContext=1)
except:
	ic=lambda *a:None if len(a)==0 else a[0] if len(a)==1 else a
from bisect import *
from sys import argv
n=input()
try:
	n=int(n)
	try:
		a=[int(w) for w in input().split()]
		# a=[n-1-w for w in a]
		n=len(a)
	except:
		n,a=1,[n]
except:
	try:
		a=[int(w) for w in n.split()]
		n=len(a)
	except:
		a=None
if a==None:
	n=int(n)
# a=[n-1-w for w in a]

# def run1(a):
# 	n=len(a)
# 	s=[n-1-w for w in a]
# 	for w in range(1,n+1):
# 		for e in range(w):
# 			if max(s[e:w])==w-e-1:
# 				return(len(a)-w)
# 	return(0)

def run2(a):
	n=len(a)
	s=[n-1-w for w in a]
	# ic(s)
	pm=[]
	zp=None
	for w in range(1,n+1):
		d=len(pm)
		for e in range(len(pm)):
			if pm[e]+e>=s[w-1]:
				d=e
				break
		pm=list(range(s[w-1],s[w-1]-d-1,-1))+[w-1 for w in pm[d:]]
		# print(pm)
		if zp==None:
			zp=s[0]
		for e in range(0,w):
			if pm[e]==0:
				return(len(a)-w)
	return(0)

cpr_c=0
def cpr(*q,**w):
	global cpr_c
	if cpr_c<20:
		print(*q,**w)
		cpr_c+=1
	else:
		print('\x1b[93mstop\x1b[0m')
		exit()

def run3(a):
	n=len(a)
	s=tuple(enumerate(a))
	ss=set()
	gp=set()
	while s not in ss:
		ss.add(s)
		gp.add(s[0])
		s=s[1:len(s)-s[0][1]]+s[:1]+s[len(s)-s[0][1]:]
	return n-len(gp)

# if len(argv)<2:
# 	print(run3(a))
# else:
# 	print(run2(a))

print(run3(a))



# # for a in '''
# # 	5 1 2 2 2 5
# # 	0 4 4 4 4
# # 	6 1 1 5 5 5 5
# # 	0 2 2
# # 	9 8 7 6 5 4 3 2 1 0
# # 	2 4 6 8 2 4 6 1 1
# # 	4 9 9 9 9 9 9 9 9 9
# # 	2 4 6 8 2 3 3 3 3 3
# # '''.split('\n'):
# # 	a=[int(w) for w in a.split()]
# # 	n=len(a)
# # 	a=[n-1-w for w in a]
# # 	if any([w<0 for w in a]):
# # 		ic(a)
# # 		a=[n-1-w for w in a]
# # 		ic(a)
# # 	if run1(a)!=run2(a):
# # 		a=[n-1-w for w in a]
# # 		ic(a)
# # 		a=[n-1-w for w in a]
# # 	a=[n-1-w for w in a]
# # 	if run1(a)!=run2(a):
# # 		a=[n-1-w for w in a]
# # 		ic(a)
# # 		a=[n-1-w for w in a]

