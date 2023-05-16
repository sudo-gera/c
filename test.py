from h import *
n=scan()
a=scan([str]*n)
while len(a)>1:
    w=0
    for q in range(1,min(len(a[0]),len(a[1]))+1):
        if a[0][-q:]==a[1][:q]:
            w=q
    a[:2]=[a[0]+a[1][w:]]
print(a[0])

