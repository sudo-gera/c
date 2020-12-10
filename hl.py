q=input()
q=';'+q+';'
c=[]
for w in range(1,len(q)):
	if q[w]!=q[w-1]:
		c.append([w])
for w in range(len(c)-1):
	c[w][0]=c[w+1][0]-c[w][0]
c=c[:-1]
c=[w[0] for w in c]
print(max(c))