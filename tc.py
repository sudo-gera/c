from bisect import *
t=int(input())
def main():
	n,m=list(map(int,input().split()))
	c=0
	y=[[-1,0] for w in range(n+1)]
	for w in range(m):
		inp=list(map(int,input().split()))
		if inp[0]!=inp[1]:
			y[inp[0]][0]=inp[1]
	for w in y:
		while w[0]!=-1 and w[1]==0:
			w[1]=1
			c+=1
			w=y[w[0]]
		if w[0]!=-1:
			c+=1
			

	'''
	for w in x:
		if w[0]!=w[1]:
			if w[2]==0:
				while 1:
					if w[2]==0:
						w[2]=1
						c+=1
						b=bisect_left(x,[w[1],-1,2])
						if b<len(x) and x[b][0]==w[1]:
							w=x[b]
						else:
							break
					else:
						c+=1
						break
	'''
	print(c)
for w in range(t):
	main()