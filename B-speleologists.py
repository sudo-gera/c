from h import *
n,m,k=scan([int,int,int])
g=scan([int]*k)
g=[w-1 for w in g]
a=scan([[int,int,int]]*m)
a=[[w[0]-1,w[1]-1,w[2]] for w in a]
s,f=scan([int,int])
s-=1
f-=1
d=[float('inf')]*n
d[f]=0
h=None
while d!=h:
    h=deepcopy(d)
    for w in a:
        d[w[1]]=min(d[w[1]],d[w[0]]+w[2])
        d[w[0]]=min(d[w[0]],d[w[1]]+w[2])
for w in g:
    if d[w]<=d[s]:
        print(-1)
        exit()
if d[s]==float('inf'):
    print(-1)
else:
    print(d[s])



