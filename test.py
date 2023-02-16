from h import *
n=scan(int)
a=scan([str]*n)
ans=[]
for q,w in enumerate(a):
    for e,r in enumerate(a):
        if q!=e and w+r==(w+r)[::-1]:
            ans.append((q+1,e+1))
ans=list(set(ans))
ans.sort()
print(len(ans))
for w in ans:
    print(*w)

