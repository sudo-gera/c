# n=int(input())
# a=[[n//2,n//2]]
# pos=[n//2-1,n//2]
# step_count=1
# field=[[0]*n for w in range(n)]
# field[n//2][n//2]=1
# while step_count<n**2:
# 	a.append(pos[:])
# 	field[pos[0]][pos[1]]=1
# 	dirs=[0,0,0,0]
# 	if pos[1]+1<n and field[pos[0]][pos[1]+1]:
# 		dirs[0]=1
# 	if pos[0]+1<n and field[pos[0]+1][pos[1]]:
# 		dirs[1]=1
# 	if pos[1]-1>0 and field[pos[0]][pos[1]-1]:
# 		dirs[2]=1
# 	if pos[0]-1>0 and field[pos[0]-1][pos[1]]:
# 		dirs[3]=1
# 	dirs=[str(w) for w in dirs]
# 	dirs=''.join(dirs)
# 	dirs+=dirs
# 	d=dirs.index('01')
# 	d%=4
# 	if d==0:
# 		pos[1]+=1
# 	if d==1:
# 		pos[0]+=1
# 	if d==2:
# 		pos[1]-=1
# 	if d==3:
# 		pos[0]-=1
# 	step_count+=1
# for q,w in enumerate(a):
# 	field[w[0]][w[1]]=q
# s=[0]*n*n
# for w in range(n):
# 	q=list(map(int,input().split()))
# 	for e in range(n):
# 		s[field[w][e]]=q[e]

# bsums=[0]*(len(s)+1)
# for w in range(len(s)):
# 	bsums[w+1]=bsums[w]+s[w]
# esums=[0]*(len(s)+1)
# for w in range(len(s)-1,-1,-1):
# 	esums[w]=esums[w+1]+s[w]
# sums=sum(s)
# m=int(input())
# for w in range(m):
# 	b1,b2,e1,e2=list(map(int,input().split()))
# 	b=field[b1-1][b2-1]
# 	e=field[e1-1][e2-1]+1
# 	print(sums-bsums[b]-esums[e])

for w in range(1):
	import os
	# os.system('./a.out '+str(w)+'\n')
	import subprocess
	subprocess.run(['a.out',str(w)])