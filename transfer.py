

def main():
    import json
    import inspect
    from fractions import Fraction
    from functools import cache
    import base64
    from functools import reduce

    def coll_sum(a,s):
        for w in a:
            s+=w
        return s

    @cache
    def pickledumps(t):
        n=t.__name__
        if t not in dumpers:
            raise TypeError\
                (f'no dumper for type \'{n}\'.')
        from pickle import dumps as picdumps
        r=picdumps(t)
        # r=base64.b64encode(r).decode()
        r=list(r)
        s=list(picdumps(int))
        s+=[0]*(len(r)-len(s))
        s=s[:len(r)]
        r=[(q-w)%256 for q,w in zip(r,s)]
        # e=[]
        # for w in r:
        #     if e and w==e[-1][0]:
        #         e[-1][1]+=1
        #     else:
        #         e.append([w,1])
        # e=coll_sum(e,[])
        # r=e
        r=tuple(r)
        return (n,r)


    @cache
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
            y=[[t]+coll_sum([w[0] for w in y],[]),t,[w[1:] for w in y]]
            return y
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
        if coll_sum([[1,1,float('inf'),0,0][int(w.kind)] for w in inspect.signature(l).parameters.values()])>1:
            return l(jloads([ts,a]),t)
        return l(jloads([ts,a]))

    def dumps(a):
        j=jdumps(a)
        t=j[0]
        j=j[1:]
        ts=set()
        t=[[ts.add(w),w][1] for w in t if w not in ts]
        d=dict(zip(*list(zip(*enumerate(t)))[::-1]))
        j=replace_types(j,d)
        t=[pickledumps(w) for w in t]
        t=coll_sum(t,())
        s=json.dumps([t,j],separators=(',',':'))
        import zlib
        s=s.encode()
        c=0
        for w in range(256):
            d=zlib.compress(s,level=9)
            if len(d)>len(s):
                break
            c+=1
            s=d
        s=bytes([c])+s
        import base64
        s=base64.b64encode(s).decode()
        return s

    def loads(a):
        import base64
        a=base64.b64decode(a.encode())
        import zlib
        c,a=a[0],a[1:]
        for w in range(c):
            a=zlib.decompress(a)
        a=a.decode()
        y=json.loads(a)
        ts=y[0]
        ts=zip(ts[::2],ts[1::2])
        ts=[pickleloads((w[0],tuple(w[1]))) for w in ts]
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