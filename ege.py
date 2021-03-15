for x in range(1,100000):
	ox=x
	a = 1
	while x > 0:
	 a *= x % 11
	 x = x // 11
	if a==120:
		print(ox)
		exit()