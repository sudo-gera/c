from __future__ import annotations;
import functools;
import json;
import traceback;
import typing;
import random;
import time;
import copy;

class ComparableProto(typing.Protocol):
    def __lt__(self: T, __other: T) -> bool: ...;
T_ = typing.TypeVar('T_');

class List(typing.Generic[T_]):
    def __init__(self, a: list[T_]|List[T_]) -> None:
        self.l : list[T_];
        if (isinstance(a, list)):
            self.l = a;
        else:
            self.l = a.l;
        self.l = copy.copy(self.l);
    def __getitem__(self, i: int) -> T_:
        assert 0 <= i;
        return self.l.__getitem__(i);
    def __setitem__(self, i: int, v: T_) -> None:
        assert 0 <= i;
        return self.l.__setitem__(i, v);
def list_size(self: List[T_]) -> int:
    return self.l.__len__();
def list_append(self: List[T_], v: T_) -> None:
    return self.l.append(v);
def list_insert(self: List[T_], i: int, v: T_) -> None:
    return self.l.insert(i, v);
def list_erase(self: List[T_], i: int) -> T_:
    return self.l.pop(i);
def list_slice_assign(self: List[T_], begin: int, end: int, val: list[T_]|List[T_]) -> None:
    assert 0 <= begin <= end <= len(self.l)
    self.l[begin:end] = val if isinstance(val, list) else val.l;
def list_contains(self: List[T_], val: T_) -> bool:
    return val in self.l;
def list_index(self: List[T_], v: T_) -> int:
    return self.l.index(v);

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore

class node(typing.Generic[T]):
    def __init__(self, *, data:List[T], down: List[node[T]|None]):
        self.data = List(data);
        self.down = List(down);
        node.check(self);

@staticmethod
def check(self: node[T]|None, s: set[int]|None = None, l: int = 0) -> None:
    if (s is None):
        s = set();
    if (self is None):
        s.add(l);
        return;
    for i in range(list_size(self.down)):
        w = self.down[i];
        node.check(w, s, l+1);
    if (l == 0):
        assert len(s) == 1;
    assert list_size(self.down) == 1 + list_size(self.data);
    assert len([w for w in self.down if w is None]) in {0, list_size(self.down)}; # type: ignore

def copy(self) -> node[T]:
    return node(data=self.data, down=self.down);

@staticmethod
def insert(self: node[T]|None, elem: T, max_len: int) -> node[T]:
    node.check(self);
    assert self is not None;
    self = self.copy();
    if (list_contains(self.data, elem)):
        t = list_index(self.data, elem);
        self.data[t] = elem;
    elif (self.down[0] is None):
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem):
            w += 1;
        list_insert(self.data, w, elem);
        list_insert(self.down, 0, None);
    else:
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem):
            w += 1;
        self.down[w] = node.insert(self.down[w], elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) > max_len):
            assert list_size(tmp.data) == 1 + max_len;
            q = tmp.copy();
            a = q.copy();
            list_slice_assign(a.data, max_len // 2,list_size(a.data), []);
            list_slice_assign(a.down, max_len // 2 + 1,list_size(a.down),[]);
            kw = q.data[max_len // 2];
            list_slice_assign(q.data, 0, max_len // 2 + 1, []);
            list_slice_assign(q.down, 0,max_len // 2 + 1, []);
            list_insert(self.data, w, kw);
            self.down[w] = q;
            list_insert(self.down, w, a);
    return self;

@staticmethod
def find_path(self: node[T], elem: T) -> list[tuple[node[T], int]] | None:
    output : list[tuple[node[T], int]] = [];
    if (node.find_path_(self, elem, output)):
        return output;
    return None;

@staticmethod
def find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool:
    node.check(self);
    if (list_contains(self.data, elem)):
        output.append((self, list_index(self.data, (elem))));
        return True;
    if (self.down[0] is None):
        return False;
    w = 0;
    while (w < list_size(self.data) and self.data[w] < elem):
        w += 1;
    tmp = self.down[w];
    assert tmp is not None;
    if (node.find_path_(tmp, elem, output)):
        output.append((self, w));
        return True;
    return False;

@staticmethod
def erase(self: node[T], elem: T, max_len: int) -> node[T]:
    node.check(self);
    t: None|node[T];
    self = self.copy();
    if (self.down[0] is None):
        t_ = list_index(self.data, (elem));
        list_erase(self.data, t_);
        list_erase(self.down, 0);
    else:
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem):
            w += 1;
        tmp = self.down[w];
        assert tmp is not None;
        self.down[w] = node.erase(tmp, elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) < max_len // 2):
            assert list_size(tmp.data) == max_len // 2 - 1;
            e = w - 1 if w else w + 1;
            q = max(w, e);
            r = min(w, e);
            tmp = self.down[e];
            assert tmp is not None;
            if (list_size(tmp.data) == max_len // 2):
                tmp = self.down[q];
                assert tmp is not None;
                t = tmp.copy();
                tmp = self.down[r];
                assert tmp is not None;
                __t = tmp.data;
                list_append(__t, self.data[r]);
                list_slice_assign(t.data, 0, 0, __t);
                tmp = self.down[r];
                assert tmp is not None;
                list_slice_assign(t.down, 0,0,tmp.down);
                list_slice_assign(self.down, r,q + 1, [t]); # type: ignore
                list_slice_assign(self.data, r,q , []);
            else:
                tmp = self.down[w];
                assert tmp is not None;
                t = tmp.copy();
                l = (q - w) * list_size(t.down);
                tmp_1 = l
                if (tmp_1 < 0):
                    tmp_1 += list_size(t.data)
                if (tmp_1 < 0):
                    tmp_1 = 0
                if (tmp_1 > list_size(t.data)):
                    tmp_1 = list_size(t.data)
                list_slice_assign(t.data, tmp_1, tmp_1, [self.data[r]]);
                tmp = self.down[e];
                assert tmp is not None;
                tmp_1 = l
                list_slice_assign(t.down, tmp_1, tmp_1, [tmp.down[(e - q + list_size(tmp.down)) % list_size(tmp.down)]]);
                self.down[w] = t;
                tmp = self.down[e];
                assert tmp is not None;
                self.data[r] = tmp.data[(e - q + list_size(tmp.data)) % list_size(tmp.data)];
                tmp = self.down[e];
                assert tmp is not None;
                t = tmp.copy();
                tmp_1 = e - q
                if (tmp_1 < 0):
                    tmp_1 += list_size(t.data);
                tmp_2 = list_size(t.data) * (q - e) + (q - w)
                if (tmp_2 < 0):
                    tmp_2 += list_size(t.data)
                list_slice_assign(t.data, tmp_1, tmp_2, []);
                tmp_1 = e - q
                if (tmp_1 < 0):
                    tmp_1 += list_size(t.down);
                tmp_2 = list_size(t.down) * (q - e) + (q - w)
                if (tmp_2 < 0):
                    tmp_2 += list_size(t.data)
                list_slice_assign(t.down, tmp_1, tmp_2, []);
                self.down[e] = t;
    return self;

@staticmethod
def to_list(self: node[T], l: list[T]) -> list[T]:
    if (self.down[0] is None):
        for i_ in range(list_size(self.data)):
            w_ = self.data[i_];
            l.append(w_);
    else:
        node.to_list(self.down[0], l);
        for w in range(list_size(self.data)):
            l.append(self.data[w]);
            tmp = self.down[w + 1];
            assert isinstance(tmp, node);
            node.to_list(tmp, l);
    return l;

@staticmethod
def chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
    self = self.copy();
    if (n):
        v = a[n][1];
        tmp = self.down[v];
        assert tmp is not None;
        self.down[v] = node.chval(tmp, a, t, kw, n - 1);
    else:
        assert self.data is not None;
        assert isinstance(t, int);
        self.data[t] = kw;
    return self;


Node = node[T] | None;


class b_set(typing.Generic[T]):

    def __init__(self) -> None:
        self.root: Node[T] = None;
        self.max_len = 99;

    def add(self, v: T) -> None:
        q = node(data=List([]), down=List([self.root, ]));
        q = node.insert(q, v, self.max_len);
        if (not list_size(q.data)):
            tmp = q.down[0];
            assert tmp is not None;
            q = tmp;
        self.root = q;

    def find(self, v: T) -> list[T]:
        r = self.root;
        if (r is None):
            return [];
        f = node.find_path(r, v);
        if (f is None):
            return [];
        _f = f[0];
        return [_f[0].data[_f[1]]];

    def __contains__(self, v: T) -> bool:
        return bool(self.find(v));

    def remove(self, v: T) -> None:
        r = self.root;
        if (r is None):
            return;
        a = node.find_path(r, v);
        if (a is None):
            return;
        a = a[::-1];
        if (a[-1][0].down[0] is not None):
            t = a[-1][0].down[list_index(a[-1][0].data, v) + 1];
            assert t is not None;
            while (t.down[0] is not None):
                t = t.down[0];
            kw = t.data[0];
            r = node.erase(r, kw, self.max_len);
            a = node.find_path(r, v);
            assert a is not None;
            del t;
            t_ = list_index(a[0][0].data, v);
            r = node.chval(r, a, t_, kw, len(a) - 1);
        else:
            r = node.erase(r, v, self.max_len);
        if (list_size(r.data) == 0):
            r = r.down[0];
        self.root = r;

    def __repr__(self) -> str:
        r = self.root;
        return repr(r);

    def to_list(self) -> list[T]:
        r = self.root;
        if (r is None):
            return [];
        return node.to_list(r, []);

    def __del__(self) -> None:
        pass;


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None):
        if (not isinstance(k, item)):
            self.k : K = k;
            self.v : V|None = v;
        else:
            self.k, self.v = k.k, k.v;

    def __lt__(self, o: item[K, V]) -> bool:
        return self.k < o.k;

    def __eq__(self, o: object|item[K, V]) -> bool:
        if (isinstance(o, item)):
            return self.k == o.k;
        return False;

    def __repr__(self) -> str:
        return 'item' + repr((self.k, self.v));

    def to_list(self) -> list[K|V|None]:
        return [self.k, self.v];


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
        self.b_set: b_set[item[K, V]] = b_set();

    def __getitem__(self, k:K)->V:
        r = self.b_set.find(item(k));
        if (not r):
            raise KeyError(k);
        tmp = r[0].v;
        assert tmp is not None;
        return tmp;

    def __setitem__(self, k:K, v:V)->None:
        self.b_set.add(item(k, v));

    def __delitem__(self, k:K)->None:
        self.b_set.remove(item(k));

    def __repr__(self)->str:
        return repr(self.b_set);

    def __contains__(self, k:K) -> bool:
        return bool(self.b_set.find(item(k)));

    def to_dict(self) -> dict[K, V]:
        r_ = self.b_set.to_list();
        r = [w.to_list() for w in r_];
        return dict(r); # type: ignore


if (__name__ == '__main__'):
    # max_len=8;

    t=time.time();
    print([time.time()-t,(t:=time.time())][0]);

    sed = random.randint(-9999, 9999);
    print(sed);
    random.seed(sed);
    s_s: b_set[int] = b_set();
    a_s = set();
    for w in range(99):
        q = random.choice([0] * 3 + [1] + [2]);
        if (q == 0):
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
        if (q == 1):
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert (r in a_s) == (r in a_s);
            assert r not in a_s or s_s.find(r)[0] == r;
        if (q == 2 and a_s):
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
        f = set(s_s.to_list());
        assert a_s == f;

    print([time.time()-t,(t:=time.time())][0]);


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0):
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1):
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        if (q == 2 and a_d):
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d):
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
        if (q == 4 and a_d):
            k = random.randint(-9999, 9999);
            while (k in a_d):
                k = random.randint(-9999, 9999);
            try:
                del a_d[k];
                assert 0;
            except KeyError:
                pass;
            del s_d[k];
        if (q == 5 and a_d):
            k = random.randint(-9999, 9999);
            while (k in a_d):
                k = random.randint(-9999, 9999);
            try:
                a_d[k];
                assert 0;
            except KeyError:
                pass;
            try:
                s_d[k];
                assert 0;
            except KeyError:
                pass;
        assert s_d.to_dict() == a_d;
        # s_d = b_dict(s_d.getstr());

    print([time.time()-t,(t:=time.time())][0]);

    a_d = dict();
    s_d = b_dict();
    for w in range(199):
        k = random.randint(-9999, 9999);
        v = random.randint(-9999, 9999);
        s_d[k] = v;
        a_d[k] = v;

    # s_d = b_dict(s_d.getstr());

    print([time.time()-t,(t:=time.time())][0]);

    w = 0;
    while (a_d):
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0):
            assert s_d.to_dict() == a_d;
    assert s_d.to_dict() == a_d;

    print([time.time()-t,(t:=time.time())][0]);

    a_d = dict();
    for w in range(999):
        k = random.randint(-9999, 9999);
        v = random.randint(-9999, 9999);
        s_d[k] = v;
        a_d[k] = v;

    print([time.time()-t,(t:=time.time())][0]);


    for w in range(19):
        q = random.choice([0] + [1] + [2] + [3]);
        if (q == 0):
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1):
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        if (q == 2 and a_d):
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d):
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];

    print([time.time()-t,(t:=time.time())][0]);

    # root_set(0.0);

    # w = 0;
    # while (a_d):
    #     k = random.choice(list(a_d));
    #     del a_d[k];
    #     del s_d[k];
    #     w += 1;
    #     if (w % 100 == 0):
    #         assert s_d.to_dict() == a_d;
    #         s_d = b_dict(s_d.getstr());
    # assert s_d.to_dict() == a_d;
    # s_d = b_dict(s_d.getstr());

    print([time.time()-t,(t:=time.time())][0]);

    a :   dict[str, str] = dict();
    s : b_dict[str, str] = b_dict();
    for q in range(10**2*3):
        funcs = {}; # type: ignore
        @(lambda x: funcs.setdefault(len(funcs), x))
        @(lambda x: funcs.setdefault(len(funcs), x))
        def add() -> None:
            k = random.randbytes(8).hex();
            v = random.randbytes(8).hex();
            assert (k in a) == (k in s);
            a[k] = v;
            s[k] = v;
            assert k in a;
            assert k in s;
            assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def mod() -> None:
            if (a):
                k = random.choice([*a.keys()]);
                v = random.randbytes(8).hex();
                assert k in a;
                assert k in s;
                a[k] = v;
                s[k] = v;
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def get() -> None:
            if (a):
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
            if (a):
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
                del a[k];
                del s[k];
                assert k not in a;
                assert k not in s;
        random.choice(funcs)();

