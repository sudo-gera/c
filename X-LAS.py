from h import *
n=scan(int)
a=scan([int]*n)
m=-1
for w in range(2**n):
    s=sum([[a[q]] if 2**q&w else [] for q in range(n)],[])
    if sorted(s)==s and len(set(s))==len(s):
        if len(s)>m:
            m=len(s)
            d=sum([[q] if 2**q&w else [] for q in range(n)],[])
print(m)
print(*d)