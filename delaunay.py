from h import *
n=scan(int)
a=scan([[int,int]*n])
s=[]
for q in a:
    for w in a:
        s.append([(q[0]-w[0])**2+(q[1]-w[1])**2,q,w])
s.sort()
d=[]
for q in s:
    for w in d:
        