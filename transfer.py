import pickle
import json
import base64
import inspect
from fractions import *
from functools import cache
loaders={}
dumpers={}
@cache
def pickledumps(t):
    import pickle
    import base64
    return base64.b64encode(pickle.dumps(t)).decode()

@cache
def pickleloads(t):
    for w in loaders:
        if pickledumps(w):
            return w

def jdumps(a):
    t=type(a)
    if t==list:
        return [t.__name__,pickledumps(t),[jdumps(w) for w in a]]
    if t in [int,str,type(None),bool]:
        return [t.__name__,pickledumps(t),a]
    if t not in dumpers:
        raise TypeError\
            (f'no dumper for {t.__name__}.')
    d=dumpers[t](a)
    return [t.__name__,pickledumps(t),jdumps(d)]

def jloads(a):
    t=a[1]
    n=a[0]
    a=a[2]
    if t in [pickledumps(w) for w in [list]]:
        return [jloads(w) for w in a]
    if t in [pickledumps(w) for w in [int,str,type(None),bool]]:
        return a
    if t not in uploaders:
        for w in loaders:
            uploaders[pickledumps(w)]=w
    if t not in uploaders:
        raise TypeError\
            (f'no loader for {n}.')
    l=loaders[uploaders[t]]
    if sum([[1,1,float('inf'),0,0][int(w.kind)] for w in inspect.signature(l).parameters.values()])>1:
        return l(jloads(a),uploaders[t])
    return l(jloads(a))

def dumps(a):
    return json.dumps(jdumps(a))

def loads(a):
    return jloads(json.loads(a))

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

@loader(float)
def load_float(a):
    return float(a)

@loader(Fraction)
def load_frac(a):
    return Fraction(*a)

@dumper(bytes,bytearray)
def dump_bytes(a):
    return base64.b64encode(a).decode()

@loader(bytes,bytearray)
def load_bytes(a,t):
    return t(base64.b64decode(a.encode()))

@dumper(set,frozenset,tuple)
def dump_set(a):
    return list(a)

@loader(set,frozenset,tuple,dict,float)
def load_simple(a,t):
    return t(a)

@dumper(dict)
def dump_dict(a):
    return list(a.items())
