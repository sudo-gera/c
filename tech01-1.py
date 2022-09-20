from h import *;
a=open(argv[1]).read();
a=a.splitlines();
a=[w.split(',') for w in a];
a=[[float(e) for e in w] for w in a];
assert len(set([len(w) for w in a]))==1;
n=len(a);
def get(z,x):
    return a[z][x];
def set(z,x,v):
    a[z][x]=v;
for w in range(n):
    if (get(w,w)==0):
        for e in range(w+1,n):
            if (get(e,w)!=0):
                s=w;
                d=e;
                f=1;
                for g in range((n+1)):
                    t=get(d,g);
                    t*=f;
                    t+=get(s,g);
                    set(s,g,t);
                break;
    if (get(w,w)!=0):
        for e in range(w+1,n):
            s=e;
            d=w;
            f=get(e,w);
            f=-f;
            f/=get(w,w);
            for g in range((n+1)):
                t=get(d,g);
                t*=f;
                t+=get(s,g);
                set(s,g,t);
for w in range(n):
    for e in range(w):
        s=e;
        d=w;
        f=get(e,w);
        f=-f;
        f/=get(w,w);
        for g in range((n+1)):
            t=get(d,g);
            t*=f;
            t+=get(s,g);
            set(s,g,t);
for w in range(n):
    print(get(w,n)/get(w,w))
