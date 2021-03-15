c=0
m=98765432
for w in range(11000,22001):
	if len(set([e for e in range(1,w+1) if w%e==0])&set([11,13,17,19]))==2:
		c+=1
		m=min(m,w)
print(c,m)