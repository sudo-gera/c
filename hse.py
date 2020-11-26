def s(n):
	o=n%17
	if o==0:
		return 2
	if o%2==0:
		return 1
	return 2

f=0
for w in range(1,2021):
	if s(w)==2:
		f+=1
print(f)