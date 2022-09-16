

def main():
    import json
    import inspect
    from fractions import Fraction
    from functools import cache
    import base64
    from functools import reduce

    # @cache
    def pickledumps(t):
        n=t.__name__
        if t not in dumpers:
            raise TypeError\
                (f'no dumper for type \'{n}\'.')
        import pickle
        r=list(pickle.dumps(t))
        s=list(pickle.dumps(int))
        s+=[0]*(len(r)-len(s))
        s=s[:len(r)]
        r=[(q-w)%256 for q,w in zip(r,s)]
        e=[]
        for w in r:
            if e and w==e[-1][0]:
                e[-1][1]+=1
            else:
                e.append([w,1])
        r=e
        return (n,r)


    # @cache
    def pickleloads(a):
        n,t=a
        for w in loaders:
            if pickledumps(w)==a:
                return w
        raise TypeError\
            (f'no loader for type \'{n}\'.')

    standart_types=[int,str,type(None),bool]
    standart_containers=[list,set,frozenset,tuple]
    loaders={w:None for w in standart_containers+standart_types}
    dumpers={w:None for w in standart_containers+standart_types}

    def jdumps(a):
        t=type(a)
        p=pickledumps(t)
        if t in standart_containers:
            y=[jdumps(w) for w in a]
            return [[t]+sum([w[0] for w in y],[]),t,[w[1:] for w in y]]
        if t in standart_types:
            return [[t],t,a]
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
        d=dict(zip(*list(zip(*enumerate(t)))[::-1]))
        j=replace_types(j,d)
        t=[pickledumps(w) for w in t]
        t=sum(t,())
        return json.dumps([t,j],separators=(',',':'))

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
        ts=y[0]
        ts=zip(ts[::2],ts[1::2])
        ts=[pickleloads(w) for w in ts]
        y[0]=ts
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

    return dumps,loads,dumper,loader
dumps,loads,dumper,loader=main()