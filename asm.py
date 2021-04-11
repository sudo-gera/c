from sys import argv
asm=open(argv[1]).read()
asm=asm.split('\n')
asm=[w.split() for w in asm]
asm=[w if w else [''] for w in asm]
i=0
a=[0]*2**6
while -1<i<len(asm):
	try:
		if asm[i][0]=='inc':
			a[int(asm[i][1])]+=1
		if asm[i][0]=='dec':
			a[int(asm[i][1])]-=1
		if asm[i][0]=='cop':
			a[int(asm[i][1])]=a[int(asm[i][2])]
		if asm[i][0]=='add':
			a[int(asm[i][1])]+=a[int(asm[i][2])]
		if asm[i][0]=='sub':
			a[int(asm[i][1])]-=a[int(asm[i][2])]
		if asm[i][0]=='mul':
			a[int(asm[i][1])]*=a[int(asm[i][2])]
		if asm[i][0]=='div':
			a[int(asm[i][1])]//=a[int(asm[i][2])]
		if asm[i][0]=='mod':
			a[int(asm[i][1])]%=a[int(asm[i][2])]
		if asm[i][0]=='cmp':
			a[int(asm[i][1])]-=a[int(asm[i][2])]
			if a[int(asm[i][1])]<0:
				a[int(asm[i][1])]=-1
			if a[int(asm[i][1])]>0:
				a[int(asm[i][1])]=1
		if asm[i][0]=='jnz':
			if a[int(asm[i][2])]:
				i=a[int(asm[i][1])]-2
		if asm[i][0]=='put':
			print(a[int(asm[i][1])])
		if asm[i][0]=='get':
			a[int(asm[i][1])]=int(input())
		if asm[i][0]=='set':
			a[int(asm[i][1])]=int(asm[i][2])
	except:
		print('error in line',i+1)
	print(i,asm[i][0],sep='\t')
	i+=1
