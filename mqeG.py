from bisect import *
n,Y,X=[int(w) for w in input().split()]
x,y1,y2=[],[],[]
for w in range(n):
	x.append(0)
	y1.append(0)
	y2.append(0)
	x[-1],y1[-1],y2[-1]=[int(w) for w in input().split()]
yb={}
ye={}
for q in range(Y+1):
	yb[q]=[]
	ye[q]=[]
for w in range(n):
	# if y1[w] not in yb:
	# 	yb[y1[w]]=[]
	yb[y1[w]].append(w)
for w in range(n):
	# if y2[w] not in ye:
	# 	ye[y2[w]]=[]
	ye[y2[w]].append(w)
z=[0,X]
ds=[[X,0,X]]
for q in range(Y+1):

	for w in yb[q]:
		e=x[w]
		if bisect_left(z,e)==bisect_right(z,e):
			insort(z,e)
			pre=z[bisect_left(z,e)-1]
			nex=z[bisect_right(z,e)]
			insort(ds, [e-pre,pre,e] )
			insort(ds, [nex-e,e,nex] )
			del ds[bisect_left(ds, [nex-pre,pre,nex] )]
		else:
			insort(z,e)

	print(ds[-1][0])


	for w in ye[q]:
		e=x[w]
		if bisect_left(z,e)-bisect_right(z,e)==-1:
			pre=z[bisect_left(z,e)-1]
			nex=z[bisect_right(z,e)]
			del ds[bisect_left(ds, [e-pre,pre,e] )]
			del ds[bisect_left(ds, [nex-e,e,nex] )]
			insort(ds, [nex-pre,pre,nex] )
		del z[z.index(x[w])]
