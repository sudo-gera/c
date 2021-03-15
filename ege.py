from functools import lru_cache
class play:
	@lru_cache
	def __init__(s,st,te,c=0):
		if c==12:
			s.none=1
			return
		s.none=0
		state=[st,te]
		s.created_from=state[:]
		if sum(state)>=90:
			s.ilen=0
			s.alen=0
			s.win=0
			s.agoto=[]
			s.igoto=[]
			return
		a=[state[:] for w in range(4)]
		a[0][0]+=1
		a[1][0]*=2
		a[2][1]+=1
		a[3][1]*=2
		a=[play(*w,c+1) for w in a]
		if not [w for w in a if w.none==0]:
			s.none=1
			return
		twa=[w for w in a if w.win]
		if twa:
			s.win=0
			s.alen=max([w.alen for w in twa])
			s.ilen=min([w.ilen for w in twa])
			s.agoto=[w.alen for w in twa].index(s.alen)
			s.igoto=[w.ilen for w in twa].index(s.ilen)
			return
		s.win=1
		s.alen=max([w.alen for w in a])
		s.ilen=min([w.ilen for w in a])
		s.agoto=[w.alen for w in a].index(s.alen)
		s.igoto=[w.ilen for w in a].index(s.ilen)
	def __str__(s):
		d=dict()
		for w in dir(s):
			if not w.startswith('__') and not w.endswith('__'):
				d[w]=eval('s.'+w)
		return str(d)
for s in range(1,86):
	print(s,play(5,s))
