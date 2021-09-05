n=input()
try:
	n=int(n)
	a=[[int(e) for e in input().split()] for w in range(n)]
except:
	from sys import stdin
	n+='\n'+stdin.read()
	a=[[int(e) for e in w.split()] for w in n.split('\n')]
	n=len(a)
from functools import total_ordering
# @total_ordering
# class cmp:
# 	def __init__(s,q):
# 		s.x,s.y=q
# 		s.a=s.x**2+s.y**2
# 	def __lt__(s,o):
# 		return [s.a,-s.y,s.x]<[o.a,-o.y,o.x]
# 	def __eq__(s,o):
# 		return s<=o and s>=o
a=[[[s[1]**2+s[0]**2,s[0],s[1]],s] for s in a]
a.sort()
a=[w[1] for w in a]
for w in a:
	print(*w)