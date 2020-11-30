task=8
if task==1:
	a=0
	from math import factorial
	for w in range(2,2021):
		a+=w*factorial(w)-w*w
		print(a)#9
if task==2:
	for ok in range(61):
		for ik in range(61):
			for ou in range(61):
				for iu in range(61):
					if 40<=ok+ik+ou+iu<=60:
						if ok*3==2*ik:
							if iu*4==3*ou:
								if ou+ok-1==iu+ik:
									print(ok)#68
if task==3:
	pass
	#2018C10/2019C11*1000
	#5.45
if task==4:
	pass
	#-1,484903
if task==5:
	pass
	#1.059901
if task==6:
	pass
	#23.41640786
	#geogebra
if task==7:
	pass
	#14.14213562
	#geogebra
if task==8:
	for w in range(1,10000):
		if 4204%w==4363%w==5105%w==5370%w:
			print(w)
	#153