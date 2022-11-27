from h import *
c=0
for q in range(10**4,10**5):
	for w in range(8):
		if 5*q%10**w + 3*q%10**w + 4*q%10**w == 13736:
			c+=1
			print(q,w)
print(c)