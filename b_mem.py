from h import *
from treeprint import *

data={}
def put(v):
    from random import randint
    k=''
    while not k or k in data:
        k=''.join(
            [
                chr(
                    randint(32,126)
                ) for w in range(
                    randint(128,1024)
                )
            ]
        )
    data[k]=v
    return k

def get(k):
    return data[k]

class l:

    def __init__(s, t=None):
        s.l = t.l if isinstance(t, l) else t if t is not None else []

    def __getitem__(s, k):
        return s.l[k]

    def __len__(s):
        return len(s.l)

    def index(s, v):
        return s.l.index(v)

    def cl(s):
        return s.l[:]

class n:

    def __init__(s, t=None):
        s.n = t.n if isinstance(t, n) else t if t is not None else []

    def __getitem__(s, k):
        t=s.n[k]
        r=t
        if type(t)!=list:
            r=[r]
        r=[w if type(w)==node else loads(get(w)) if w!=None else w for w in r]
        if type(t)!=list:
            r=r[0]
        s.n[k]=r
        return r

    def __len__(s):
        return len(s.n)

    def index(s, v):
        return s.n.index(v)

    def cl(s):
        return s.n[:]

max_len = 8

def dumps(q):
    import json
    return json.dumps({
        'data':[list(w) if type(w)==item else [w] for w in q.data.l],
        'next':q.next.n
    } if q!=None else q)

def loads(q):
    import json
    q=json.loads(q)
    if q!=None:
        q['data']=[item(*w) if len(w)==2 else w[0] for w in q['data']]
    return node(**q) if q!=None else q

class node:
    def __init__(s, *, data=None, next=None):
        if data is None:
            data = []
        if next is None:
            next = [None]
        # next=[w if type(w)==str else put(dumps(w)) if w!=None else w for w in next]
        s._data = l(data)
        s._next = n(next)
        s.mem=1

    @property
    def next(s):
        return s._next

    @property
    def data(s):
        return s._data

def memup(s):
    s._next=n([w if type(w)==str else put(dumps(w)) if w!=None else w for w in s._next.n])



def check(s, r=1):
    assert len(s.data) + 1 == len(s.next)
    assert len(s.data) <= max_len
    if s.next[0] is None:
        assert list(s.data) == sorted(s.data)
    assert r or max_len // 2 <= len(s.data)
    if s.next[0] is None:
        return [s.data[0], s.data[-1]]
    a = [check(w, 0) for w in s.next]
    for w in range(len(s.data)):
        assert a[w][1] < s.data[w] < a[w + 1][0]
    return [a[0][0], a[-1][1]]


def insert(s, k):
    if k in s.data:
        t = s.data.index(k)
        s = node(next=s.next, data=s.data[:t] + [k] + s.data[t + 1:])
    elif s.next[0] is None:
        w = 0
        while w < len(s.data) and s.data[w] < k:
            w += 1
        s = node(data=s.data[:w] + [k] + s.data[w:], next=[None] + s.next.cl())
    else:
        w = 0
        while w < len(s.data) and s.data[w] < k:
            w += 1
        s = node(data=s.data, next=s.next[:w] +
                 [insert(s.next[w], k)] + s.next[w + 1:])
        if len(s.next[w].data) > max_len:
            assert len(s.next[w].data) == 1 + max_len
            q = s.next[w]
            a = node(data=q.data[:max_len // 2],
                     next=q.next[:max_len // 2 + 1])
            d = q.data[max_len // 2]
            q = node(data=q.data[max_len // 2 + 1:],
                     next=q.next[max_len // 2 + 1:])
            s = node(next=s.next[:w] + [a, q] + s.next[w + 1:],
                     data=s.data[:w] + [d] + s.data[w:])
    memup(s)
    return s


def find(s, k):
    if k in s.data:
        return [[s,s.data.index(k)]]
    if s.next[0] is None:
        return None
    w = 0
    while w < len(s.data) and s.data[w] < k:
        w += 1
    r = find(s.next[w], k)
    if r is not None:
        r.append([s,w])
    return r


def erase(s, k):
    if s.next[0] is None:
        t = s.data.index(k)
        s = node(data=s.data[:t] + s.data[t + 1:], next=s.next[1:])
    else:
        w = 0
        while w < len(s.data) and s.data[w] < k:
            w += 1
        s = node(data=s.data, next=s.next[:w] +
                 [erase(s.next[w], k)] + s.next[w + 1:])
        if len(s.next[w].data) < max_len // 2:
            assert len(s.next[w].data) == max_len // 2 - 1
            if w:
                if len(s.next[w - 1].data) == max_len // 2:
                    s = node(data=s.data, next=s.next[:w -
                                                      1] +
                             [node(data=s.next[w -
                                               1].data.cl() +
                                   [s.data[w -
                                           1]] +
                                   s.next[w].data.cl(), next=s.next[w -
                                                                    1].next.cl() +
                                   s.next[w].next.cl())] +
                             s.next[w:])
                    s = node(data=s.data[:w - 1] + s.data[w:],
                             next=s.next[:w] + s.next[w + 1:])
                else:
                    s = node(data=s.data,
                             next=s.next[:w] + [node(data=[s.data[w - 1]] + s.next[w].data.cl(),
                                                     next=[s.next[w - 1].next[-1]] + s.next[w].next.cl())] + s.next[w + 1:])
                    s = node(
                        next=s.next, data=s.data[:w - 1] + [s.next[w - 1].data[-1]] + s.data[w:])
                    s = node(data=s.data,
                             next=s.next[:w - 1] + [node(data=s.next[w - 1].data[:-1],
                                                         next=s.next[w - 1].next[:-1])] + s.next[w:])
            elif len(s.next[w + 1].data) == max_len // 2:
                s = node(data=s.data, next=s.next[:w] +
                         [node(data=s.next[w].data.cl() +
                               [s.data[w]] +
                               s.next[w +
                                      1].data.cl(), next=s.next[w].next.cl() +
                               s.next[w +
                                      1].next.cl())] +
                         s.next[w +
                                1:])
                s = node(data=s.data[:w] + s.data[w + 1:],
                         next=s.next[:w + 1] + s.next[w + 2:])
            else:
                s = node(data=s.data,
                         next=s.next[:w] + [node(data=s.next[w].data.cl() + [s.data[w]],
                                                 next=s.next[w].next.cl() + [s.next[w + 1].next[0]])] + s.next[w + 1:])
                s = node(next=s.next,
                         data=s.data[:w] + [s.next[w + 1].data[0]] + s.data[w + 1:])
                s = node(data=s.data,
                         next=s.next[:w + 1] + [node(data=s.next[w + 1].data[1:],
                                                     next=s.next[w + 1].next[1:])] + s.next[w + 2:])
    memup(s)
    return s


def to_list(s, l):
    if s.next[0] is None:
        for w in s.data:
            l.append(w)
    else:
        to_list(s.next[0], l)
        for w in range(len(s.data)):
            l.append(s.data[w])
            to_list(s.next[w + 1], l)
    return l


def chval(s, a, t, d, n):
    if n:
        v=a[n][1]
        s = node(data=s.data,
                 next=s.next[:v] + [chval(s.next[v],
                                          a,
                                          t,
                                          d,
                                          n - 1)] + s.next[v + 1:])
    else:
        s = node(next=s.next, data=s.data[:t] + [d] + s.data[t + 1:])
    return s


class b:

    def __init__(s):
        s.s = None

    def check(s):
        return
        if s.s is not None:
            check(s.s)

    def add(s, v):
        # s.s=loads(get(s.s)) if s.s!=None else s.s
        s.check()
        q = node(next=[s.s])
        q = insert(q, v)
        s.s = q
        if not s.s.data:
            s.s = s.s.next[0]
        s.check()
        # s.s=put(dumps(s.s)) if s.s!=None else s.s

    def find(s, v):
        # r=s.s
        # s.s=loads(get(s.s)) if s.s!=None else s.s
        s.check()
        if s.s is None:
            return []
        f = find(s.s, v)
        if f is None:
            return []
        f = f[0][0]
        # s.s=r
        return [f.data[f.data.index(v)]]

    def remove(s, v):
        # s.s=loads(get(s.s)) if s.s!=None else s.s
        s.check()
        if s.s is None:
            return
        a = find(s.s, v)
        if a is None:
            return
        a = a[::-1]
        if a[-1][0].next[0] is not None:
            t = a[-1][0].next[a[-1][0].data.index(v) + 1]
            while t.next[0] is not None:
                t = t.next[0]
            d = t.data[0]
            s.s = erase(s.s, d)
            a = find(s.s, v)
            t = a[0][0].data.index(v)
            s.s = chval(s.s, a, t, d, len(a) - 1)
        else:
            s.s = erase(s.s, v)
        if len(s.s.data) == 0:
            s.s = s.s.next[0]
        s.check()
        # s.s=put(dumps(s.s)) if s.s!=None else s.s

    def __repr__(s):
        # r=s.s
        # s.s=loads(get(s.s)) if s.s!=None else s.s
        treeprint(s.s)
        # s.s=r
        return ''

    def to_list(s):
        # r=s.s
        # s.s=loads(get(s.s)) if s.s!=None else s.s
        if s.s is None:
            ret=[]
        else:
            ret=to_list(s.s, [])
        # s.s=r
        return ret

@total_ordering
class item:

    def __init__(s, k, v=None):
        s.k = k
        s.v = v

    def __lt__(s, o):
        return s.k < o.k

    def __eq__(s, o):
        return s.k == o.k

    def __repr__(s):
        return 'item'+repr([s.k, s.v])

    def __getitem__(s, n):
        return [s.k, s.v][n]


class d:

    def __init__(s):
        s.b = b()

    def __getitem__(s, k):
        return s.b.find(item(k))[0].v

    def __setitem__(s, k, v):
        s.b.add(item(k, v))

    def __delitem__(s, k):
        s.b.remove(item(k))

    def __repr__(s):
        return repr(s.b)

    def __contains__(s, k):
        return bool(s.b.find(item(k)))

    def to_dict(s):
        return dict(s.b.to_list())


s = b()
sed = randint(-9999, 9999)
print(sed)
seed(sed)
a = set()
for w in range(99):
    q = choice([0] * 3 + [1] + [2])
    if q == 0:
        r = randint(-9999, 9999)
        a.add(r)
        s.add(r)
    if q == 1:
        r = choice(list(a)) if a and randint(0, -1 + 2) else randint(0, -1 + 9)
        assert (r in a) == bool(s.find(r))
        assert r not in a or s.find(r)[0] == r
    if q == 2 and a:
        r = choice(list(a))
        a.remove(r)
        s.remove(r)
    f = set(s.to_list())
    assert a == f
a = dict()
s = d()
for w in range(999):
    q = choice([0] * 3 + [1] + [2] + [3])
    if q == 0:
        k = choice(list(a)) if a and randint(0, 1) else randint(-9999, 9999)
        v = randint(-9999, 9999)
        a[k] = v
        s[k] = v
    if q == 1:
        k = choice(list(a)) if a and randint(0, 1) else randint(-9999, 9999)
        assert (k in a) == (k in s)
    if q == 2 and a:
        k = choice(list(a))
        a[k] == s[k]
    if q == 3 and a:
        k = choice(list(a))
        del a[k]
        del s[k]
    assert s.to_dict() == a
