from h import *
n,m=scan([int,int])
a=scan([[[int,float('inf')]]*m]*n)
a[0][0][1]=0
d=None
while d!=a:
    d=deepcopy(a)
    for q in range(n):
        for w in range(m):
            for z,x in [[q+1,w],[q-1,w],[q,w+1],[q,w-1]]:
                if 0<=z<n and 0<=x<m:
                    l=max(a[z][x][0]-a[q][w][0],0)
                    a[z][x][1]=min(a[z][x][1],a[q][w][1]+l)
print(a[-1][-1][1])




