def main():
	a1x,a1y,b1x,b1y=[int(w) for w in input().split()]
	a2x,a2y,b2x,b2y=[int(w) for w in input().split()]



	t2=((a1x-a2x)*(b1y-a1y)-(a1y-a2y)*(b1x-a1x))
	try:
		t2/=((b2x-a2x)*(b1y-a1y)-(b2y-a2y)*(b1x-a1x))
	except:
		if t2:
			print('NO')
		else:
			if a1x<=a2x<=b1x or b1x<=a2x<=a1x or a1x<=b2x<=b1x or b1x<=b2x<=a1x or a2x<=a1x<=b2x or b2x<=a1x<=a2x or a2x<=b1x<=b2x or b2x<=b1x<=a2x or \
				a1y<=a2y<=b1y or b1y<=a2y<=a1y or a1y<=b2y<=b1y or b1y<=b2y<=a1y or a2y<=a1y<=b2y or b2y<=a1y<=a2y or a2y<=b1y<=b2y or b2y<=b1y<=a2y:
				print('YES')
			else:
				print('NO')
		return
	t1=((b2y-a2y)*t2-(a1y-a2y))
	try:
		t1/=(b1y-a1y)
	except:
		if t2:
			print('NO')
		else:
			if a1x<=a2x<=b1x or b1x<=a2x<=a1x or a1x<=b2x<=b1x or b1x<=b2x<=a1x or a2x<=a1x<=b2x or b2x<=a1x<=a2x or a2x<=b1x<=b2x or b2x<=b1x<=a2x or \
				a1y<=a2y<=b1y or b1y<=a2y<=a1y or a1y<=b2y<=b1y or b1y<=b2y<=a1y or a2y<=a1y<=b2y or b2y<=a1y<=a2y or a2y<=b1y<=b2y or b2y<=b1y<=a2y:
				print('YES')
			else:
				print('NO')
		return 

	x=a1x+(b1x-a1x)*t1
	y=a1y+(b1y-a1y)*t1

	if (a1x-x>=0 and b1x-x<=0 or a1x-x<=0 and b1x-x>=0) and (a1y-y>=0 and b1y-y<=0 or a1y-y<=0 and b1y-y>=0) and (a2x-x>=0 and b2x-x<=0 or a2x-x<=0 and b2x-x>=0) and (a2y-y>=0 and b2y-y<=0 or a2y-y<=0 and b2y-y>=0):
		print('YES')
	else:
		print('NO')

main()