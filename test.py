from h import *
a=scan(str)
n=scan(int)
s=scan([str]*n)
for q in s:
    d=[w for w in range(len(a)) if a[w:].startswith(q)]
    if d:
        print(len(d),d[0])
    else:
        print(0,0)






