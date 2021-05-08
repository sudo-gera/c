ps=[2]
for w in range(3,50001,2):
	p=1
	for e in ps:
		if w%e==0:
			p=0
			break
	if p:
		ps.append(w)

ns=[1]
for w in range(20):
	ns=[w*e for w in ns for e in ps]
	ns=[w for w in ns if w<50001]


q=[]
# for w in range(10001,50001):
for w in ns:
	c=0
	for e in range(1,w+1):
		if w%e==0:
			c+=1
		if c>17:
			break
	if c>17:
		q.append(w)
print(len(q))
print(q[0])