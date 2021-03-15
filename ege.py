for s in range(1,1000):
	os=s
	n = 36
	while s < 2020:
	 s = s * 2
	 n = n + 3
	print(n)
	if n==60:
		print(os)
		exit()