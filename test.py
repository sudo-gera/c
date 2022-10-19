from h import *
s=1
c=0
for q in range(s):
    n=100
    a=[[] for w in range(n)]
    for w in range(n):
        for e in range(w):
            if rand(4):
                a[w]+=[e]
                a[e]+=[w]
    for w in range(n):
        for e in range(w):
            for r in range(e):
                if e in a[w] and r in a[e] and w in a[r]:
                    c+=1
print(c/s)