from h import *
from treeprint import *
# data={}
# def put(v):
#     from random import randint
#     k=''
#     while not k or k in data:
#         k=''.join(
#             [
#                 chr(
#                     randint(32,126)
#                 ) for w in range(
#                     randint(128,1024)
#                 )
#             ]
#         )
#     data[k]=v
#     return k

# def get(k):
#     return data[k]

allow_set=1

class l:
    def __init__(s,t=None):
        s.l=t.l if type(t)==l else t if t!=None else []
    def __getitem__(s,k):
        return s.l[k]
    def __setitem__(s,k,v):
        assert allow_set
        s.l[k]=v
    def __len__(s):
        return len(s.l)
    def index(s,v):
        return s.l.index(v)
    def cl(s):
        return s.l[:]

n=l

max_len=4
class node:
    def __init__(s,*,data=None,next=None):
        if data==None:
            data=[]
        if next==None:
            next=[None]
        # if type(next)==n:
        #     next=next.l
        # if type(data)==l:
        #     data=data.l
        s._data=l(data)
        s._next=n(next)
        s.mem=0
    @property
    def next(s):
        return s._next
    @property
    def data(s):
        return s._data
    @next.setter
    def next(s,v):
        assert allow_set
        s._next=l(v)
        s.mem=1
    @data.setter
    def data(s,v):
        assert allow_set
        s._data=l(v)
        s.mem=1
    def memup(s):
        for w in range(len(s.next)):
            if s.next[w].mem:
                s.next=s.next[:w]+[node(
                    data=s.next[w].data,
                    next=s.next[w].next
                )]+s.next[w+1:]

def check(s,r=1):
    assert len(s.data)+1==len(s.next)
    assert len(s.data)<=max_len
    if s.next[0]==None:
        assert list(s.data)==sorted(s.data)
    assert r or max_len//2<=len(s.data)
    assert s.mem==0
    if s.next[0]==None:
        return [s.data[0],s.data[-1]]
    a=[check(w,0) for w in s.next]
    for w in range(len(s.data)):
        assert a[w][1]<s.data[w]<a[w+1][0]
    return [a[0][0],a[-1][1]]

def insert(s,k):
    if k in s.data:
        t=s.data.index(k)
        s.data=s.data[:t]+[k]+s.data[t+1:]
    elif s.next[0]==None:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        s=node(
            data=s.data[:w]+[k]+s.data[w:],
            next=[None]+s.next.cl()
        )
    else:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        s.next=s.next[:w]+[insert(s.next[w],k)]+s.next[w+1:]
        if len(s.next[w].data)>max_len:
            assert len(s.next[w].data)==1+max_len
            q=s.next[w]
            s.next=s.next[:w]+[None]+s.next[w+1:]
            a=node(
                data=q.data[:max_len//2],
                next=q.next[:max_len//2+1]
            )
            d=q.data[max_len//2]
            q=node(
                data=q.data[max_len//2+1:],
                next=q.next[max_len//2+1:]
            )
            s.next=s.next[:w]+[a,q]+s.next[w+1:]
            s.data=s.data[:w]+[d]+s.data[w:]
        s.memup()
    return s

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
        s=node(
            data=s.data[:t]+s.data[t+1:],
            next=s.next[1:]
        )
    else:
        w=0
        while w<len(s.data) and s.data[w]<k:
            w+=1
        s=node(data=s.data,next=s.next[:w]+[erase(s.next[w],k)]+s.next[w+1:])
        if len(s.next[w].data)<max_len//2:
            assert len(s.next[w].data)==max_len//2-1
            if w:
                if len(s.next[w-1].data)==max_len//2:
                    s.next[w-1]=node(
                        data=s.next[w-1].data.cl()+[s.data[w-1]]+s.next[w].data.cl(),
                        next=s.next[w-1].next.cl()+s.next[w].next.cl()
                    )
                    s=node(
                        data=s.data[:w-1]+s.data[w:],
                        next=s.next[:w]+s.next[w+1:]
                    )
                else:
                    s.next[w]=node(
                        data=[s.data[w-1]]+s.next[w].data.cl(),
                        next=[s.next[w-1].next[-1]]+s.next[w].next.cl()
                    )
                    s=node(next=s.next,data=s.data[:w-1]+[s.next[w-1].data[-1]]+s.data[w:])
                    s.next[w-1]=node(
                        data=s.next[w-1].data[:-1],
                        next=s.next[w-1].next[:-1]
                    )
            else:
                if len(s.next[w+1].data)==max_len//2:
                    s.next[w]=node(
                        data=s.next[w].data.cl()+[s.data[w]]+s.next[w+1].data.cl(),
                        next=s.next[w].next.cl()+s.next[w+1].next.cl()
                    )
                    s.data=s.data[:w]+s.data[w+1:]
                    s.next=s.next[:w+1]+s.next[w+2:]
                else:
                    s.next[w].data=s.next[w].data.cl()+[s.data[w]]
                    s.next[w].next=s.next[w].next.cl()+[s.next[w+1].next[0]]
                    s.data=s.data[:w]+[s.next[w+1].data[0]]+s.data[w+1:]
                    s.next[w+1].data=s.next[w+1].data[1:]
                    s.next[w+1].next=s.next[w+1].next[1:]
        s.memup()
    return s

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
        q=node(next=[s.s])
        q=insert(q,v)
        s.s=q
        if not s.s.data:
            s.s=s.s.next[0]
        if s.s!=None and s.s.mem:
            s.s=node(
                data=s.s.data,
                next=s.s.next
            )
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
            s.s=erase(s.s,d)
            a=find(s.s,v)
            t=a[0].data.index(v)
            a[0].data=a[0].data[:t]+[d]+a[0].data[t+1:]
            for w in a[1:]:
                w.memup()
        else:
            s.s=erase(s.s,v)
        if len(s.s.data)==0:
            s.s=s.s.next[0]
        if s.s!=None and s.s.mem:
            s.s=node(
                data=s.s.data,
                next=s.s.next
            )
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
        return repr([s.k,s.v])
    def __getitem__(s,n):
        return [s.k,s.v][n]

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
    def to_dict(s):
        return dict(s.b.to_list())
    


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
for w in range(999):
    q=choice([0]*3+[1]+[2]+[3])
    if q==0:
        k=choice(list(a)) if a and randint(0,1) else randint(-9999,9999)
        v=randint(-9999,9999)
        a[k]=v
        s[k]=v
    if q==1:
        k=choice(list(a)) if a and randint(0,1) else randint(-9999,9999)
        assert (k in a) == (k in s)
    if q==2 and a:
        k=choice(list(a))
        a[k]==s[k]
    if q==3 and a:
        k=choice(list(a))
        del a[k]
        del s[k]
    assert s.to_dict()==a