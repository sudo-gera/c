n=int(input())
a=[[int(e) for e in input().split()] for w in range(n)]
from functools import total_ordering
@total_ordering
class cmp:
	def __init__(s,q):
		s.x,s.y=q
		s.a=s.x**2+s.y**2
	def __lt__(s,o):
		return [s.a,-s.y,s.x]<[o.a,-o.y,o.x]
	def __eq__(s,o):
		return s<=o and s>=o
a.sort(key=cmp)
for w in a:
	for e in a:
		print(w<e)
for w in a:
	print(*w)