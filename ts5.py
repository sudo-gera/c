from h import *
n=scan(int)
a=scan([int]*n)
s=[]
for w in range(1,n+1):
    for q in range(w):
        if sum(a[q:w])==0:
            s.append((q,w))
c=0
for w in range(1,n+1):
    for q in range(w):
        for e in s:
            if q<=e[0] and e[1]<=w:
                c+=1
                break
print(c)


