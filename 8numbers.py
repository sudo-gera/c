from sys import stdin
a=stdin.read().strip().split()
class num:
	def __init__(s,q):
		s.q=q
	def __lt__(s,o):
		return s.q+o.q<o.q+s.q 
a.sort(key=num)
a=a[::-1]
for w in a:
	print(w,end='')
print()

