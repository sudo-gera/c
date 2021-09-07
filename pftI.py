a,b=[int(w) for w in [input(),input()]]
w=2
da={}
while (w*w<=a):
	while a%w==0:
		if w not in da:
			da[w]=1
		else:
			da[w]+=1
		a//=w
	w+=1
if a!=1:
	w=a
	if w not in da:
		da[w]=1
	else:
		da[w]+=1
	a//=w
w=2
db={}
while (w*w<=b):
	while b%w==0:
		if w not in db:
			db[w]=1
		else:
			db[w]+=1
		b//=w
	w+=1
if b!=1:
	w=b
	if w not in db:
		db[w]=1
	else:
		db[w]+=1
	b//=w
for w in da:
	if w not in db:
		db[w]=0
for w in db:
	if w not in da:
		da[w]=0
r=1
for w in da:
	r*=w**max(da[w],db[w])
print(r)