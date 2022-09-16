from functools import *
from random import *
from treeprint import *
max_len=4
class node:
    def __init__(s,*,data=None,next=None):
        if data==None:
            data=[]
        if next==None:
            next=[None]
        s.data=data
        s.next=next

def check(s,r=1):
    # assert len(s.data)+1==len(s.next)
    assert len(s.data)<=max_len
    if s.next[0]==None:
        assert list(s.data)==sorted(s.data)
    assert r or max_len//2<=len(s.data)
    if s.next[0]==None:
        return [s.data[0],s.data[-1]]
    a=[check(w,0) for w in s.next]
    for w in range(len(s.data)):
        assert a[w][1]<s.data[w]<a[w+1][0]
    return [a[0][0],a[-1][1]]

def insert(s,k):
    if k in s.data:
        s.data[s.data.index(k)]=k
        return
    if s.next[0]==None:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        s.data[w:w]=[k]
        s.next[:0]=[None]
    else:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        insert(s.next[w],k)
        if len(s.next[w].data)>max_len:
            assert len(s.next[w].data)==1+max_len
            q=s.next[w]
            s.next[w]=None
            a=node(
                data=q.data[:max_len//2],
                next=q.next[:max_len//2+1]
            )
            d=q.data[max_len//2]
            q=node(
                data=q.data[max_len//2+1:],
                next=q.next[max_len//2+1:]
            )
            s.next[w:w+1]=[a,q]
            s.data[w:w]=[d]

def find(s,k):
    if k in s.data:
        return [s]
    if s.next[0]==None:
        return None
    w=0
    while w<len(s.data) and s.data[w]<k:
        w+=1
    r=find(s.next[w],k)
    if r!=None:
        r.append(s)
    return r

def erase(s,k):
    if s.next[0]==None:
        t=s.data.index(k)
        s.data[t:t+1]=[]
        s.next[:1]=[]
    else:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        erase(s.next[w],k)
        if len(s.next[w].data)<max_len//2:
            assert len(s.next[w].data)==max_len//2-1
            if w:
                if len(s.next[w-1].data)==max_len//2:
                    s.next[w-1].data+=[s.data[w-1]]+s.next[w].data
                    s.next[w-1].next+=s.next[w].next
                    s.data[w-1:w]=[]
                    s.next[w:w+1]=[]
                else:
                    s.next[w].data[:0]=[s.data[w-1]]
                    s.next[w].next[:0]=[s.next[w-1].next[-1]]
                    s.data[w-1]=s.next[w-1].data[-1]
                    s.next[w-1].data[-1:]=[]
                    s.next[w-1].next[-1:]=[]
            else:
                if len(s.next[w+1].data)==max_len//2:
                    s.next[w].data+=[s.data[w]]+s.next[w+1].data
                    s.next[w].next+=s.next[w+1].next
                    s.data[w:w+1]=[]
                    s.next[w+1:w+2]=[]
                else:
                    s.next[w].data+=[s.data[w]]
                    s.next[w].next+=[s.next[w+1].next[0]]
                    s.data[w]=s.next[w+1].data[0]
                    s.next[w+1].data[:1]=[]
                    s.next[w+1].next[:1]=[]

def to_list(s,l):
    if s.next[0]==None:
        for w in s.data:
            l.append(w)
    else:
        to_list(s.next[0],l)
        for w in range(len(s.data)):
            l.append(s.data[w])
            to_list(s.next[w+1],l)
    return l


class b:
    def __init__(s):
        s.s=None
    def check(s):
        if s.s!=None:
            check(s.s)
    def add(s,v):
        s.check()
        q=node()
        q.next[0]=s.s
        insert(q,v)
        if q.data:
            s.s=q
        s.check()
    def find(s,v):
        s.check()
        if s.s==None:
            return []
        f=find(s.s,v)
        if f == None:
            return []
        f=f[0]
        return [f.data[f.data.index(v)]]
    def remove(s,v):
        s.check()
        if s.s==None:
            return
        a=find(s.s,v)
        if a==None:
            return
        a=a[::-1]
        if a[-1].next[0]!=None:
            t=a[-1].next[a[-1].data.index(v)+1]
            while t.next[0]!=None:
                t=t.next[0]
            d=t.data[0]
            erase(s.s,d)
            a=find(s.s,v)
            a[0].data[a[0].data.index(v)]=d
        else:
            erase(s.s,v)
        if len(s.s.data)==0:
            s.s=s.s.next[0]
        s.check()
    def __repr__(s):
        treeprint(s.s)
        return ''
    def to_list(s):
        if s.s==None:
            return []
        return to_list(s.s,[])

@total_ordering
class item:
    def __init__(s,k,v=None):
        s.k=k
        s.v=v
    def __lt__(s,o):
        return s.k<o.k
    def __eq__(s,o):
        return s.k==o.k
    def __repr__(s):
        return repr({s.k:s.v})

class d:
    def __init__(s):
        s.b=b()
    def __getitem__(s,k):
        return s.b.find(item(k))[0].v
    def __setitem__(s,k,v):
        s.b.add(item(k,v))
    def __delitem__(s,k):
        s.b.remove(item(k))
    def __repr__(s):
        return repr(s.b)
    def __contains__(s,k):
        return bool(s.b.find(item(k)))


s=b()
sed=randint(-9999,9999)
# seed=8400934794700124356
print(sed)
seed(sed)
a=set()
for w in range(999):
    q=choice([0]*3+[1]+[2])
    if q==0:
        r=randint(-9999,9999)
        # print(q,r)
        a.add(r)
        s.add(r)
    if q==1:
        r=choice(list(a)) if a and randint(0,-1+2) else randint(0,-1+9)
        # print(q,r)
        assert (r in a)==bool(s.find(r))
        assert (r not in a) or s.find(r)[0]==r
    if q==2 and a:
        r=choice(list(a))
        # print(q,r)
        a.remove(r)
        s.remove(r)
    f=set(s.to_list())
    assert a==f

a=dict()
s=d()
for w in range(9999):
    q=choice([0]+[1]+[2]+[3])
    if q==0:
        k=choice(list(a)) if a and randint(0,-1+2) else randint(-9999,9999)
        v=randint(-9999,9999)
        a[k]=v
        s[k]=v
    if q==1:
        k=choice(list(a)) if a and randint(0,-1+2) else randint(-9999,9999)
        assert (k in a) == (k in s)
    if q==2 and a:
        k=choice(list(a))
        a[k]==s[k]
    if q==3 and a:
        k=choice(list(a))
        del a[k]
        del s[k]
        