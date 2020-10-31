from itertools import permutations
class busi:
	def __init__(s,q):
		s.q=q
	def __eq__(s,o):
		q=s.q[:]
		for w in range(6):
			if q[w:]+q[:w]==o.q:
				return 1
		q=q[::-1]
		for w in range(6):
			if q[w:]+q[:w]==o.q:
				return 1
		return 0
cs=[]


for w in range(32):
	s=[(w>>e)%2 for e in range(5)]
	pe=[busi(w) for w in permutations(s)]
	u=[]
	for w in pe:
		if w not in u:
			u.append(w)
	cs.append(len(u))


cs=sorted(list(set(cs)))[::-1]
print(cs)