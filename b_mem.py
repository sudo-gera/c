from __future__ import annotations
import functools
import json
import traceback
import typing
import random
import time
from db import *

__all__ = [
    'b_dict',
    'b_set',
    'put',
    'get',
    'root_get',
    'root_set',
    'home',
    'url',
    'typechecked'
]

max_len = 64


class ComparableProto(typing.Protocol):
    def __lt__(self: T, __other: T) -> bool: ...


T = typing.TypeVar('T', bound=ComparableProto)
T = typing.TypeVar('T')  # type: ignore


class node(typing.Generic[T]):

    def __repr__(self):
        return 'node' + repr((self.key,self.kw))

    @typechecked
    def __init__(self, key: url | Node = None, **kw):
        self.key: url | None
        self.kw: dict[str, list]
        if isinstance(key, node):
            kw |= key.kw
            key = key.key
        for w in kw:
            kw[w] = list(kw[w])
        assert key is None or isinstance(key, url)
        self.key = key
        self.kw = kw

    def load(self):
        if not self.kw:
            qd = json.loads(get(self.key).decode())
            self.kw = {
                'data': [
                    item(*w) if len(w) == 2 else w[0] for w in qd['data']
                ],
                'down': [
                    node(url(w)) if w else None for w in qd['down']
                ],
            }
        assert all([isinstance(w, node | None) for w in self.kw['down']])

    @property  # type: ignore
    @typechecked
    def down(self) -> list[tn]:
        self.load()
        return self.kw['down']

    @property  # type: ignore
    @typechecked
    def data(self) -> list[T]:
        self.load()
        return self.kw['data']

    def mutable(self) -> node[T]:
        self.load()
        r: node = node(self)
        r.key = None
        return r

    @staticmethod
    @typechecked
    def dumps(self: Node) -> url:
        if self is None:
            return url()
        assert isinstance(self, node)
        if self.key is not None:
            return self.key
        r = {
            'data': [item(w).to_list() if isinstance(w, item) else [w] for w in self.data],
            'down': [str(node.dumps(w)) for w in self.down]
        }
        er = json.dumps(r).encode()
        u = put(er)
        self.key = u
        return u

    @staticmethod
    @typechecked
    def insert(self: node[T], k: T):
        self = self.mutable()
        if k in self.data:
            t = self.data.index(k)
            self.data[t] = k
        elif self.down[0] is None:
            w = 0
            while w < len(self.data) and self.data[w] < k:
                w += 1
            self.data[w:w] = [k]
            self.down[:0] = [None]
        else:
            w = 0
            while w < len(self.data) and self.data[w] < k:
                w += 1
            self.down[w] = node.insert(self.down[w], k)
            if len(self.down[w].data) > max_len:
                assert len(self.down[w].data) == 1 + max_len
                q: Node
                a: Node
                q = self.down[w].mutable()
                a = q.mutable()
                a.data[max_len // 2:] = []
                a.down[max_len // 2 + 1:] = []
                kw = q.data[max_len // 2]
                q.data[:max_len // 2 + 1] = []
                q.down[:max_len // 2 + 1] = []
                self.data[w:w] = [kw]
                self.down[w:w + 1] = [a, q]
        return self

    @staticmethod
    @typechecked
    def find(self: node[T], k: T) -> list[tuple[node[T], int]] | None:
        if k in self.data:
            return [(self, self.data.index(k))]
        if self.down[0] is None:
            return None
        w = 0
        while w < len(self.data) and self.data[w] < k:
            w += 1
        r = node.find(self.down[w], k)
        if r is not None:
            r.append((self, w))
        return r

    @staticmethod
    @typechecked
    def erase(self: node[T], k: T) -> node[T]:
        t: Node
        self = self.mutable()
        if self.down[0] is None:
            t = self.data.index(k)
            self.data[t:t + 1] = []
            self.down[:1] = []
        else:
            w = 0
            while w < len(self.data) and self.data[w] < k:
                w += 1
            self.down[w] = node.erase(self.down[w], k)
            if len(self.down[w].data) < max_len // 2:
                assert len(self.down[w].data) == max_len // 2 - 1
                e = w - 1 if w else w + 1
                q = max(w, e)
                r = min(w, e)
                if len(self.down[e].data) == max_len // 2:
                    t = self.down[q].mutable()
                    t.data[:0] = self.down[r].data + [self.data[r]]
                    t.down[:0] = self.down[r].down
                    self.down[r:q + 1] = [t]
                    self.data[r:q] = []
                else:
                    t = self.down[w].mutable()
                    l = (q - w) * len(t.down)
                    t.data[l:l] = [self.data[r]]
                    t.down[l:l] = [self.down[e].down[e - q]]
                    self.down[w] = t
                    self.data[r] = self.down[e].data[e - q]
                    t = self.down[e].mutable()
                    t.data[e - q: len(t.data) * (q - e) + (q - w)] = []
                    t.down[e - q: len(t.down) * (q - e) + (q - w)] = []
                    self.down[e] = t
        return self

    @staticmethod
    @typechecked
    def to_list(self: node[T], l: list[T]) -> list[T]:
        if self.down[0] is None:
            for w in self.data:
                l.append(w)
        else:
            node.to_list(self.down[0], l)
            for w in range(len(self.data)):
                l.append(self.data[w])
                node.to_list(self.down[w + 1], l)
        return l

    @staticmethod
    @typechecked
    def chval(self: node[T], a, t, kw, n) -> node[T]:
        self = self.mutable()
        if n:
            v = a[n][1]
            self.down[v] = node.chval(self.down[v], a, t, kw, n - 1)
        else:
            self.data[t] = kw
        return self


Node = node[T] | None
tn = node
tn = Node  # type: ignore


class b_set(typing.Generic[T]):

    def __init__(self, u: url = url()):
        self.root: Node = None
        if u:
            self.root = node(url(get(u).decode()))

    def add(self, v):
        q = node(data=[], down=[self.root, ])
        q = node.insert(q, v)
        if not q.data:
            q = q.down[0]
        self.root = q

    def find(self, v):
        r = self.root
        if r is None:
            return []
        f = node.find(r, v)
        if f is None:
            return []
        f = f[0]
        return [f[0].data[f[1]]]

    def __contains__(self, v):
        return bool(self.find(v))

    def remove(self, v):
        r = self.root
        if r is None:
            return
        a = node.find(r, v)
        if a is None:
            return
        a = a[::-1]
        if a[-1][0].down[0] is not None:
            t = a[-1][0].down[a[-1][0].data.index(v) + 1]
            while t.down[0] is not None:
                t = t.down[0]
            kw = t.data[0]
            r = node.erase(r, kw)
            a = node.find(r, v)
            t = a[0][0].data.index(v)
            r = node.chval(r, a, t, kw, len(a) - 1)
        else:
            r = node.erase(r, v)
        if len(r.data) == 0:
            r = r.down[0]
        self.root = r

    def __repr__(self):
        r = self.root
        return repr(r)

    @typechecked
    def to_list(self) -> list:
        r = self.root
        if r is None:
            return []
        return node.to_list(r, [])

    @typechecked
    def getstr(self) -> url:
        x = node.dumps(self.root)
        return put(str(x).encode(), m=1) if x else x

    def __del__(self):
        try:
            node.dumps(self.root)
        except Exception:
            print(traceback.format_exc())
        assert self.root is None or self.root.key, 'All unsaved data was deleted!'


K = typing.TypeVar('K', bound=ComparableProto)
K = typing.TypeVar('K')  # type: ignore
V = typing.TypeVar('V')


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k, v=None):
        if isinstance(k, item):
            k, v = k.k, k.v
        self.k = k
        self.v = v

    def __lt__(self, o):
        return self.k < o.k

    def __eq__(self, o):
        return self.k == o.k

    def __repr__(self):
        return 'item' + repr((self.k, self.v))

    def to_list(self):
        return [self.k, self.v]


class b_dict(typing.Generic[K, V]):

    def __init__(self, u: url = url()):
        self.b_set: b_set[item[K, V]] = b_set(u)

    @typechecked
    def __getitem__(self, k:K)->V:
        r = self.b_set.find(item(k))
        if not r:
            raise KeyError(k)
        return r[0].v

    @typechecked
    def __setitem__(self, k:K, v:V)->None:
        self.b_set.add(item(k, v))

    @typechecked
    def __delitem__(self, k:K)->None:
        self.b_set.remove(item(k))

    @typechecked
    def __repr__(self)->str:
        return repr(self.b_set)

    @typechecked
    def __contains__(self, k:K) -> bool:
        return bool(self.b_set.find(item(k)))

    @typechecked
    def to_dict(self) -> dict:
        r = self.b_set.to_list()
        r = [w.to_list() for w in r]
        return dict(r)

    @typechecked
    def getstr(self) -> url:
        return self.b_set.getstr()


if __name__ == '__main__':
    assert root_get is None

    max_len=8

    root_set(0.0)

    t=time.time()
    print([time.time()-t,(t:=time.time())][0])

    sed = random.randint(-9999, 9999)
    # sed = -3676
    print(sed)
    random.seed(sed)
    s_s: b_set[int] = b_set()
    a_s = set()
    for w in range(99):
        q = random.choice([0] * 3 + [1] + [2])
        if q == 0:
            r = random.randint(-9999, 9999)
            a_s.add(r)
            s_s.add(r)
        if q == 1:
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9)
            assert (r in a_s) == (r in a_s)
            assert r not in a_s or s_s.find(r)[0] == r
        if q == 2 and a_s:
            r = random.choice(list(a_s))
            a_s.remove(r)
            s_s.remove(r)
        f = set(s_s.to_list())
        assert a_s == f

    print([time.time()-t,(t:=time.time())][0])
    # for w in range(199):
    #     r = random.randint(-9999, 9999)
    #     a_s.add(r)
    #     s_s.add(r)
    #     f = set(s_s.to_list())
    #     assert a_s == f

    # while a_s:
    #     r = random.choice(list(a_s))
    #     a_s.remove(r)
    #     s_s.remove(r)
    #     f = set(s_s.to_list())
    #     assert a_s == f


    a_d: dict[int, int] = dict()
    s_d: b_dict[int, int] = b_dict()
    for w in range(49):
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6])
        if q == 0:
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999)
            v = random.randint(-9999, 9999)
            a_d[k] = v
            s_d[k] = v
        if q == 1:
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999)
            assert (k in a_d) == (k in s_d)
        if q == 2 and a_d:
            k = random.choice(list(a_d))
            a_d[k] == s_d[k]
        if q == 3 and a_d:
            k = random.choice(list(a_d))
            del a_d[k]
            del s_d[k]
        if q == 4 and a_d:
            k = random.randint(-9999, 9999)
            while k in a_d:
                k = random.randint(-9999, 9999)
            try:
                del a_d[k]
                assert 0
            except KeyError:
                pass
            del s_d[k]
        if q == 5 and a_d:
            k = random.randint(-9999, 9999)
            while k in a_d:
                k = random.randint(-9999, 9999)
            try:
                a_d[k]
                assert 0
            except KeyError:
                pass
            try:
                s_d[k]
                assert 0
            except KeyError:
                pass
        assert s_d.to_dict() == a_d
        s_d = b_dict(s_d.getstr())

    print([time.time()-t,(t:=time.time())][0])

    a_d = dict()
    s_d = b_dict()
    for w in range(199):
        k = random.randint(-9999, 9999)
        v = random.randint(-9999, 9999)
        s_d[k] = v
        a_d[k] = v

    s_d = b_dict(s_d.getstr())

    print([time.time()-t,(t:=time.time())][0])

    w = 0
    while a_d:
        k = random.choice(list(a_d))
        del a_d[k]
        del s_d[k]
        w += 1
        if w % 100 == 0:
            assert s_d.to_dict() == a_d
            s_d = b_dict(s_d.getstr())
    assert s_d.to_dict() == a_d
    s_d = b_dict(s_d.getstr())

    print([time.time()-t,(t:=time.time())][0])

    a_d = dict()
    for w in range(999):
        k = random.randint(-9999, 9999)
        v = random.randint(-9999, 9999)
        s_d[k] = v
        a_d[k] = v

    print([time.time()-t,(t:=time.time())][0])

    s_d = b_dict(s_d.getstr())


    root_set(0.1)
    for w in range(19):
        q = random.choice([0] + [1] + [2] + [3])
        if q == 0:
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999)
            v = random.randint(-9999, 9999)
            a_d[k] = v
            s_d[k] = v
        if q == 1:
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999)
            assert (k in a_d) == (k in s_d)
        if q == 2 and a_d:
            k = random.choice(list(a_d))
            a_d[k] == s_d[k]
        if q == 3 and a_d:
            k = random.choice(list(a_d))
            del a_d[k]
            del s_d[k]

    print([time.time()-t,(t:=time.time())][0])

    root_set(0.0)

    # w = 0
    # while a_d:
    #     k = random.choice(list(a_d))
    #     del a_d[k]
    #     del s_d[k]
    #     w += 1
    #     if w % 100 == 0:
    #         assert s_d.to_dict() == a_d
    #         s_d = b_dict(s_d.getstr())
    # assert s_d.to_dict() == a_d
    # s_d = b_dict(s_d.getstr())

    print([time.time()-t,(t:=time.time())][0])

