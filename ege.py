q=[]
# for w in range(10001,50001):
for w in range(10001,50001):
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