import json as json
import inspect as inspect
from fractions import Fraction as Fraction
from functools import cache as cache
import base64 as base64
from queue import Queue
from functools import reduce
from random import shuffle

@cache
def pickledumps(t):
    import pickle
    return (t.__name__,base64.b64encode(pickle.dumps(t)).decode())


@cache
def pickleloads(a):
    n,t=a
    for w in loaders:
        if pickledumps(w)==a:
            return w
    raise TypeError\
        (f'no loader for {n}.')

standart_types=[int,str,type(None),bool]
standart_containers=[list,set,frozenset,tuple]
loaders={w:None for w in standart_containers+standart_types}
dumpers={w:None for w in standart_containers+standart_types}

def dumps(x):
    ts=[]
    d={}
    q=Queue()
    q.put(x)
    r=id(x)
    while not q.empty():
        a=q.get()
        t=type(a)
        ts.append(t)
        if id(a) in d:
            continue
        d[id(a)]=[a]
        if t in standart_containers:
            for w in a:
                q.put(w)
            d[id(a)]+=[t]+[id(w) for w in a]
        elif t in standart_types:
            d[id(a)]+=[t,a]
        elif t not in dumpers:
                raise TypeError\
                    (f'no dumper for type {t._name__}.')
        else:
            _d=dumpers[t](a)
            d[id(a)]+=[t,id(_d)]
            q.put(_d)
    ts=list(set(ts))
    td=dict(zip(*list(zip(*enumerate(ts)))[::-1]))
    dl=list(d)
    dl=[r]+[w for w in dl if w!=r]
    nd=dict(zip(*list(zip(*enumerate(dl)))[::-1]))
    for w in d:
        if d[w][1] in standart_types:
            d[w]=[td[d[w][1]]]+d[w][2:]
        else:
            d[w]=[td[d[w][1]]]+[nd[e] for e in d[w][2:]]
    d={nd[w]:d[w] for w in d}
    d=sorted(list(d.items()))
    d=list(list(zip(*d))[1])
    ts=[pickledumps(w) for w in ts]
    return json.dumps([ts,d])

def __loads(a,d):
    q,t,a=a[0],a[1],a[2:]
    if q in d:
        return a
    d.add(q)
    if t in standart_containers:
        return t([__loads(w,d) for w in a])
    a=a[0]
    if t in standart_types:
        return a
    l=loaders[t]
    if sum([[1,1,float('inf'),0,0][int(w.kind)] for w in inspect.signature(l).parameters.values()])>1:
        return l(__loads(a,d),t)
    return l(__loads(a,d))

def _loads(a):
    a=json.loads(a)
    t,a=a
    t=[pickleloads(tuple(w)) for w in t]
    a=[[q,t[w[0]]]+w[1:] for q,w in enumerate(a)]
    for w in a:
        if w[1] not in standart_types:
            w[2:]=[a[e] for e in w[2:]]
    a=a[0]
    a=__loads(a,set())
    return a

def jloads(a):
    ts=a[0]
    a=a[1]
    t=ts[a[0]]
    a=a[1]
    if t in standart_containers:
        return t([jloads([ts,w]) for w in a])
    if t in standart_types:
        return a
    l=loaders[t]
    if sum([[1,1,float('inf'),0,0][int(w.kind)] for w in inspect.signature(l).parameters.values()])>1:
        return l(jloads([ts,a]),t)
    return l(jloads([ts,a]))

def loads(a):
    y=json.loads(a)
    y[0]=[pickleloads(tuple(w)) for w in y[0]]
    return jloads(y)

def dumper(*t):
    def dumper_f(f):
        for w in t:
            dumpers[w]=f
        return f
    return dumper_f

def loader(*t):
    def loader_f(f):
        for w in t:
            loaders[w]=f
        return f
    return loader_f

@dumper(float)
def dump_float(a):
    return Fraction(a)

@dumper(Fraction)
def dump_frac(a):
    return [a.numerator,a.denominator]

@loader(Fraction)
def load_frac(a):
    return Fraction(*a)

@dumper(bytes,bytearray)
def dump_bytes(a):
    return base64.b64encode(a).decode()

@loader(bytes,bytearray)
def load_bytes(a,t):
    return t(base64.b64decode(a.encode()))

@loader(dict,float)
def load_simple(a,t):
    return t(a)

@dumper(dict)
def dump_dict(a):
    return list(a.items())

a={1:2,'1':'2'}
a[3]=a
