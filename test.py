from h import *
k=80
for x in range(-k,k+1):
	for y in range(-k,k+1):
		for z in range(-k,k+1):
			if 2*x**2 + y**4 + 4*z**2 + 2*x**2*y**4 - 42*z + 33 == 0:
				print(x,y,z)


