from h import *
n,m=scan([int]*2)
a=scan([[int]*2]*m)
s=[set() for w in range(n)]
for q,w in a:
    s[q-1].add(w-1)
    s[w-1].add(q-1)
a=s
def count(a,n):
    a=deepcopy(a)
    s=set(range(n))
    c=0
    while s:
        c+=1
        q=Queue()
        q.put(next(iter(s)))
        while not q.empty():
            t=q.get()
            if t in s:
                for w in a[t]:
                    q.put(w)
                s.remove(t)
    return c
ac=count(a,n)
r=[]
for q in range(n):
    s=deepcopy(a)
    s[q]=set()
    for w in s:
        if q in w:
            w.remove(q)
    sc=count(s,n)-1
    if sc>ac:
        r.append(q+1)
r.sort()
print(len(r))
print(*r)