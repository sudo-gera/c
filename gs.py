task=4
if task==1:
	a=0
	from math import factorial
	for w in range(1,2021):
		a+=w*factorial(w)-w**2*(-1)**w
	print(a)
if task==2:
	for a in range(60):
		for b in range(60):
			for c in range(60):
				for d in range(60):
					if 40<=a+b+c+d<=60:
						if 3*a==2*b:
							if 4*d==c:
								if a+c-1==b+d:
									print(a,b,c,d)
if task==3:
	a=0
	for w in range(1001,10000,2):
		if all([e not in str(w) for e in '6789']):
			a+=w
	print(a)
if task==8:
	for w in range(1,6000):
		if 4204%w==4363%w==5105%w==5370%w:
			print(w)