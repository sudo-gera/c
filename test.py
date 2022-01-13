for q in range(10**6,10**7):
	if all([w!='0' for w in str(q)]):
		if all([
			q%int(str(q)[w:])==0
		for w in range(len(str(q)))]):
			print(q)
	if q%10**6==0:
		print(q/10**7)

