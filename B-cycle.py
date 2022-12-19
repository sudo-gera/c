from copyreg import pickle
from h import *
n,m=scan([int]*2)
a=scan([[int,int]]*m)
d={}
for q in range(1,n+1):
    d[q]=set()
for q,w in a:
    d[q]|={w}
f=''
while 1:
    if any([
        w in d[w]
        for w in d
    ]):
        print('YES')
        exit()
    if f==modules.pickle.dumps(d):
        print('NO')
        exit()
    f=modules.pickle.dumps(d)
    for w in d:
        h=set()
        for e in d[w]:
            h|=d[e]
        d[w]|=h


