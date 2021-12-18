from pprint import pprint
from sys import *
argv=[int(w) for w in argv[1:]]
nums=[]
while len(nums)<sum(argv):
	nums+=[int(w) for w in input().split()]
stdin=nums
a=[0]
[a.append(a[-1]+w) for w in argv]
a=zip(a,a[1:])
a=[stdin[w[0]:w[1]] for w in a]
s=[[]]
for d in a:
	s=[r+[w]
		for w in enumerate(d)
			for r in s]
s=[[
	[e[0]
		for e in w],
	[e[1]
		for e in w]]
			for w in s]
s=[w[1] for w in s if len(set(w[0]))==len(w[0])]
from functools import reduce
s=[reduce(lambda a,s:a*s,w,1) for w in s]
s=sum(s)
print(s)