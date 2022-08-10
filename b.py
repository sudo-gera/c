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

max_len=5
class node:
    def __init__(s):
        s.data=[]
        s.next=[None]
    def insert(s,k):
        if k in s.data:
            return
        if s.next[0]==None:
            w=0
            while w<len(s.data) and s.data[w]<k:
                w+=1
            s.data.insert(w,k)
            s.next.append(None)
        else:
            w=0
            while w<len(s.data) and s.data[w]<k:
                w+=1
            s.next[w].insert(k)
            if len(s.next[w].data)>max_len:
                assert len(s.next[w].data)==1+max_len
                q=s.next[w]
                s.next[w]=None
                a=node()
                a.data=q.data[:max_len//2]
                a.next=q.next[:max_len//2+1]
                d=q.data[max_len//2]
                q.data=q.data[max_len//2+1:]
                q.next=q.next[max_len//2+1:]
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
        r=s.next[w].find(k)
        if r!=None:
            r.append(s)
        return r
    def erase(s,k):
        if s.next[0]==None:
            s.data.remove(k)
            s.next.pop()
        else:
            w=0
            while w<len(s.data) and s.data[w]<k:
                w+=1
            s.next[w].erase(k)
            if len(s.next[w].data)<max_len//2:
                assert len(s.next[w].data)==max_len//2-1
                if w:
                    if len(s.next[w-1].data)==max_len//2:
                        s.next[w-1].data+=[s.data[w-1]]+s.next[w].data
                        s.next[w-1].next+=s.next[w].next
                        s.data[w-1:w]=[]
                        s.next[w:w+1]=[]
                    else:
                        s.next[w].data+=[s.data[w-1]]
                        s.next[w].next+=[s.next[w-1].next[-1]]
                        s.data[w]=s.next[w-1].data[-1]
                        s.next[w-1].data[-2:]=[]
                        s.next[w-1].next[-2:]=[]
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
            l+=s.data
        else:
            s.next[0].to_list(l)
            for w in range(len(s.data)):
                l.append(data[w])
                s.next[0].to_list(l)
        return l


class b:
    def __init__(s):
        s.s=None
    def check(s,r=1):
        if s.s==None:
            f=float('inf')
            return [-f,f]
        assert len(s.s.data)+1==len(s.s.next)
        assert len(s.s.data)<=max_len
        if r:
            return [s.s.data[0],s.s.data[-1]]
        assert max_len//2<=len(s.s.data)
        if s.s.next[0]==None:
            return [s.s.data[0],s.s.data[-1]]
        a=[w.check(0) for w in s.s.next]
        for w in range(len(s.s.data)):
            assert a[w][1]<s.s.data[w]<a[w+1][0]
        return [a[0][0],a[-1][1]]
    def add(s,v):
        s.check()
        q=node()
        q.next[0]=s.s
        q.insert(v)
        if q.data:
            s.s=q
        s.check()
    def find(s,v):
        s.check()
        if s.s==None:
            return []
        f=s.s.find(v)
        if f == None:
            return []
        f=f[0]
        return [f.data[f.data.index(v)]]
    def remove(s,v):
        s.check()
        if s.s==None:
            return
        a=s.s.find(v)
        if a==None:
            return
        a=a[::-1]
        if a[-1].next[0]!=None:
            t=a[-1].next[a[-1].data.index(v)+1]
            while t.next[0]!=None:
                t=t.next[0]
            d=t.data[0]
            s.s.erase(d)
            a=s.s.find(v)
            a[0].data[a[0].data.index(v)]=d
        else:
            s.s.erase(v)
        if len(s.s.data)==0:
            s.s=None
        s.check()
    def __repr__(s):
        treeprint(s.s)
        return ''
    def to_list(s):
        if s.s==None:
            return []
        return s.s.to_list([])




s=b()
seed=rand()
seed=2805934230260850707
print(seed)
random.seed(seed)
a=set()
for w in range(999):
    q=choice([0]+[1]*3+[2])
    if q==0:
        r=rand()
        print(q,r)
        a.add(r)
        s.add(r)
    if q==1:
        r=choice(list(a)) if a and rand(2) else rand()
        print(q,r)
        assert (r in a)==bool(s.find(r))
        assert (r not in a) or s.find(r)[0]==r
    if q==2 and a:
        r=choice(list(a))
        print(q,r)
        a.remove(r)
        s.remove(r)