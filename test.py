from h import *
p,f=scan([str]*2)
p=[p[w:]+p[:w] for w in range(len(p))]
ans=[]
for q in range(len(f)):
    if f[q:q+len(p[0])] in p:
        ans.append(q)
print(*ans)


