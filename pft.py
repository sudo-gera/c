ps=[]
for w in range(3,10**7,2):
	g=1
	for e in ps:
		if w%e==0:
			g=0
			break
	if g:
		ps.append(w)
ps=[2]+ps
print(ps)