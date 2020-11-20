f,g=0,0
for w in range(10**7,10**7*2):
	s=str(w)[1:]
	if s[0]==s[-1] and s[1]==s[-2] and s[2]==s[-3]:
		f+=1
	g+=1
print(f,g)