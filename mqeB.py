ps=[2]
q=3
while ps[-1]<10**5:
	for w in ps:
		if q%w==0:
			break
	else:
		ps.append(q)
	q+=2
print(ps)