import json as _json
import inspect as _inspect
from fractions import Fraction as _Fraction
from functools import cache as _cache
import base64 as _base64

@_cache
def _pickledumps(t):
    import pickle
    return _base64.b64encode(pickle._dumps(t)).decode()


@_cache
def _pickleloads(t):
    for w in _loaders:
        if _pickledumps(w)==t:
            return w
    raise TypeError\
        (f'no loader for {t}.')

_standart_types=[int,str,type(None),bool]
_standart_containers=[list,set,frozenset,tuple]
_loaders={w:None for w in _standart_containers+_standart_types}
_dumpers={w:None for w in _standart_containers+_standart_types}

def _jloads(a):
    p=a[1]
    n=a[0]
    a=a[2]
    t=_pickleloads(p)
    if t in _standart_containers:
        return t([_jloads(w) for w in a])
    if t in _standart_types:
        return a
    l=_loaders[t]
    if sum([[1,1,float('inf'),0,0][int(w.kind)] for w in _inspect.signature(l).parameters.values()])>1:
        return l(_jloads(a),t)
    return l(_jloads(a))

def _jdumps(a):
    t=type(a)
    p=_pickledumps(t)
    if t in _standart_containers:
        # y=list(zip(*[_jdumps(w) for w in a]))
        # return [[t]+sum(y[0],[]),y[1]]
        return [t.__name__,p,[_jdumps(w) for w in a]]
    if t in _standart_types:
        return [t.__name__,p,a]
    if t not in _dumpers:
        raise TypeError\
            (f'no dumper for {t.__name__}.')
    d=_dumpers[t](a)
    return [t.__name__,p,_jdumps(d)]

    

def dumps(a):
    j=_jdumps(a)

    return _json.dumps(_jdumps(a))

def loads(a):
    return _jloads(_json.loads(a))

def dumper(*t):
    def _dumper_f(f):
        for w in t:
            _dumpers[w]=f
        return f
    return _dumper_f

def loader(*t):
    def _loader_f(f):
        for w in t:
            _loaders[w]=f
        return f
    return _loader_f

@dumper(float)
def _dump_float(a):
    return _Fraction(a)

@dumper(_Fraction)
def _dump_frac(a):
    return [a.numerator,a.denominator]

@loader(_Fraction)
def _load_frac(a):
    return _Fraction(*a)

@dumper(bytes,bytearray)
def _dump_bytes(a):
    return _base64.b64encode(a).decode()

@loader(bytes,bytearray)
def _load_bytes(a,t):
    return t(_base64.b64decode(a.encode()))

@loader(dict,float)
def _load_simple(a,t):
    return t(a)

@dumper(dict)
def _dump_dict(a):
    return list(a.items())
