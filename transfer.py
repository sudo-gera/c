import json as json
import inspect as inspect
from fractions import Fraction as Fraction
from functools import cache as cache
import base64 as base64
from queue import Queue
from functools import reduce

@cache
def pickledumps(t):
    import pickle
    return (t.__name__,base64.b64encode(pickle.dumps(t)).decode())


@cache
def pickleloads(a):
    for w in loaders:
        if pickledumps(w)==a:
            return w
    raise TypeError\
        (f'no loader for {n}.')

standart_types=[int,str,type(None),bool]
standart_containers=[list,set,frozenset,tuple]
loaders={w:None for w in standart_containers+standart_types}
dumpers={w:None for w in standart_containers+standart_types}

def _dumps(x):
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
    ts=set(list(ts))
    td=dict(zip(*list(zip(*enumerate(ts)))[::-1]))
    # nd=dict(zip(*list(zip(*enumerate(d)))[::-1]))
    for w in d:
    #     if d[w][1] in standart_types:
            d[w]=[td[d[w][1]]]+d[w][2:]
        # d[w]=td[d[w][1]],[nd[e] for e in d[w][2:]]
    return [r,ts,d]

def jdumps(a):
    t=type(a)
    p=pickledumps(t)
    if t in standart_containers:
        y=[jdumps(w) for w in a]
        return [[t]+sum([w[0] for w in y],[]),t,[w[1:] for w in y]]
    if t in standart_types:
        return [[t],t,a]
    if t not in dumpers:
        raise TypeError\
            (f'no dumper for type {t._name__}.')
    d=dumpers[t](a)
    d=jdumps(d)
    return [[t]+d[0],t,d[1:]]

def replace_types(a,t):
    if a[0] in standart_containers:
        return [t[a[0]],[replace_types(w,t) for w in a[1]]]
    if a[0] in standart_types:
        return [t[a[0]],a[1]]
    return [t[a[0]],replace_types(a[1],t)]

def dumps(a):
    j=jdumps(a)
    t=j[0]
    j=j[1:]
    t=[t[w] for w in range(len(t)) if all([t[w]!=t[e] for e in range(w)])]
    # t=list(set(t))
    d=dict(zip(*list(zip(*enumerate(t)))[::-1]))
    j=replace_types(j,d)
    t=[pickledumps(w) for w in t]
    return json.dumps([t,j])

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
