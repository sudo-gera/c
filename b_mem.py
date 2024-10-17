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
    def __init__(self, a: list[T_]|List[T_]) -> None\
    :
    # { // BEGIN
        self.l : list[T_];
        if (isinstance(a, list))\
        :
        # { // BEGIN
            self.l = a;
        else\
        :
        # { // BEGIN
            self.l = a.l;
        self.l = copy.copy(self.l);
    def __getitem__(self, i: int) -> T_\
    :
    # { // BEGIN
        assert 0 <= i;
        return self.l.__getitem__(i);
    def __setitem__(self, i: int, v: T_) -> None\
    :
    # { // BEGIN
        assert 0 <= i;
        return self.l.__setitem__(i, v);
def list_size(self: List[T_]) -> int\
:
# { // BEGIN
    return self.l.__len__();
# } // END
def list_append(self: List[T_], v: T_) -> None\
:
# { // BEGIN
    return self.l.append(v);
# } // END
def list_insert(self: List[T_], i: int, v: T_) -> None\
:
# { // BEGIN
    return self.l.insert(i, v);
# } // END
def list_erase(self: List[T_], i: int) -> T_\
:
# { // BEGIN
    return self.l.pop(i);
# } // END
def list_slice_assign(self: List[T_], begin: int, end: int, val: list[T_]|List[T_]) -> None\
:
# { // BEGIN
    assert 0 <= begin <= end <= len(self.l)
    self.l[begin:end] = val if isinstance(val, list) else val.l;
# } // END
def list_contains(self: List[T_], val: T_) -> bool\
:
# { // BEGIN
    return val in self.l;
# } // END
def list_index(self: List[T_], v: T_) -> int\
:
# { // BEGIN
    return self.l.index(v);
# } // END

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore

# } // END
class node(typing.Generic[T]):
    def __init__(self, *, data:List[T], down: List[node[T]|None])\
    :
    # { // BEGIN
        self.data = List(data);
        self.down = List(down);

# } // END
def node_copy(self: node[T]) -> node[T]\
:
# { // BEGIN
    return node(data=self.data, down=self.down);
# } // END


def node_insert(self: node[T]|None, elem: T, max_len: int) -> node[T]\
:
# { // BEGIN
    (self);
    assert self is not None;
    self = node_copy(self)
    if (list_contains(self.data, elem))\
    :
    # { // BEGIN
        t = list_index(self.data, elem);
        self.data[t] = elem;
    # } // END
    elif (self.down[0] is None)\
    :
    # { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)\
        :
        # { // BEGIN
            w += 1;
        # } // END
        list_insert(self.data, w, elem);
        list_insert(self.down, 0, None);
    # } // END
    else\
    :
    # { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)\
        :
        # { // BEGIN
            w += 1;
        # } // END
        self.down[w] = node_insert(self.down[w], elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) > max_len)\
        :
        # { // BEGIN
            assert list_size(tmp.data) == 1 + max_len;
            q = node_copy(tmp);
            a = node_copy(q);
            list_slice_assign(a.data, max_len // 2,list_size(a.data), []);
            list_slice_assign(a.down, max_len // 2 + 1,list_size(a.down),[]);
            kw = q.data[max_len // 2];
            list_slice_assign(q.data, 0, max_len // 2 + 1, []);
            list_slice_assign(q.down, 0,max_len // 2 + 1, []);
            list_insert(self.data, w, kw);
            self.down[w] = q;
            list_insert(self.down, w, a);
        # } // END
    # } // END
    return self;
# } // END

def node_find_path(self: node[T], elem: T) -> list[tuple[node[T], int]] | None\
:
# { // BEGIN
    output : list[tuple[node[T], int]] = [];
    if (node_find_path_(self, elem, output))\
    :
    # { // BEGIN
        return output;
    # } // END
    return None;
# } // END

def node_find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool\
:
# { // BEGIN
    (self);
    if (list_contains(self.data, elem))\
    :
    # { // BEGIN
        output.append((self, list_index(self.data, (elem))));
        return True;
    # } // END
    if (self.down[0] is None)\
    :
    # { // BEGIN
        return False;
    # } // END
    w = 0;
    while (w < list_size(self.data) and self.data[w] < elem)\
    :
    # { // BEGIN
        w += 1;
    # } // END
    tmp = self.down[w];
    assert tmp is not None;
    if (node_find_path_(tmp, elem, output))\
    :
    # { // BEGIN
        output.append((self, w));
        return True;
    # } // END
    return False;
# } // END

def node_erase(self: node[T], elem: T, max_len: int) -> node[T]\
:
# { // BEGIN
# { // BEGIN
    (self);
    t: None|node[T];
    self = node_copy(self);
    if (self.down[0] is None)\
    :
    # { // BEGIN
        t_ = list_index(self.data, (elem));
        list_erase(self.data, t_);
        list_erase(self.down, 0);
    # } // END
    else\
    :
    # { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)\
        :
        # { // BEGIN
            w += 1;
        # } // END
        tmp = self.down[w];
        assert tmp is not None;
        self.down[w] = node_erase(tmp, elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) < max_len // 2)\
        :
        # { // BEGIN
            assert list_size(tmp.data) == max_len // 2 - 1;
            if (w)\
            :
            # { // BEGIN
                e = w - 1;
            # } // END
            else\
            :
            # { // BEGIN
                e = w + 1;
            q = max(w, e);
            r = min(w, e);
            tmp = self.down[e];
            assert tmp is not None;
            if (list_size(tmp.data) == max_len // 2)\
            :
            # { // BEGIN
                tmp = self.down[q];
                assert tmp is not None;
                t = node_copy(tmp);
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
            # } // END
            else\
            :
            # { // BEGIN
                tmp = self.down[w];
                assert tmp is not None;
                t = node_copy(tmp);
                l = (q - w) * list_size(t.down);
                tmp_1 = l
                if (tmp_1 < 0)\
                :
                # { // BEGIN
                    tmp_1 += list_size(t.data)
                # } // END
                if (tmp_1 < 0)\
                :
                # { // BEGIN
                    tmp_1 = 0
                # } // END
                if (tmp_1 > list_size(t.data))\
                :
                # { // BEGIN
                    tmp_1 = list_size(t.data)
                # } // END
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
                t = node_copy(tmp);
                tmp_1 = e - q
                if (tmp_1 < 0)\
                :
                # { // BEGIN
                    tmp_1 += list_size(t.data);
                # } // END
                tmp_2 = list_size(t.data) * (q - e) + (q - w)
                if (tmp_2 < 0)\
                :
                # { // BEGIN
                    tmp_2 += list_size(t.data)
                # } // END
                list_slice_assign(t.data, tmp_1, tmp_2, []);
                tmp_1 = e - q
                if (tmp_1 < 0)\
                :
                # { // BEGIN
                    tmp_1 += list_size(t.down);
                # } // END
                tmp_2 = list_size(t.down) * (q - e) + (q - w)
                if (tmp_2 < 0)\
                :
                # { // BEGIN
                    tmp_2 += list_size(t.data)
                # } // END
                list_slice_assign(t.down, tmp_1, tmp_2, []);
                self.down[e] = t;
            # } // END
        # } // END
    # } // END
    return self;
# } // END

def node_to_list(self: node[T], l: list[T]) -> list[T]\
:
# { // BEGIN
    if (self.down[0] is None)\
    :
    # { // BEGIN
        for i_ in range(list_size(self.data)):
            w_ = self.data[i_];
            l.append(w_);
    else\
    :
    # { // BEGIN
        node_to_list(self.down[0], l);
        for w in range(list_size(self.data)):
            l.append(self.data[w]);
            tmp = self.down[w + 1];
            assert isinstance(tmp, node);
            node_to_list(tmp, l);
    return l;

def node_chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]\
:
# { // BEGIN
    self = node_copy(self);
    if (n)\
    :
    # { // BEGIN
        v = a[n][1];
        tmp = self.down[v];
        assert tmp is not None;
        self.down[v] = node_chval(tmp, a, t, kw, n - 1);
    else\
    :
    # { // BEGIN
        assert self.data is not None;
        assert isinstance(t, int);
        self.data[t] = kw;
    return self;


Node = node[T] | None;


class b_set(typing.Generic[T]):

    def __init__(self) -> None\
    :
    # { // BEGIN
        self.root: Node[T] = None;
        self.max_len = 99;

    def add(self, v: T) -> None\
    :
    # { // BEGIN
        q = node(data=List([]), down=List([self.root, ]));
        q = node_insert(q, v, self.max_len);
        if (not list_size(q.data))\
        :
        # { // BEGIN
            tmp = q.down[0];
            assert tmp is not None;
            q = tmp;
        self.root = q;

    def find(self, v: T) -> list[T]\
    :
    # { // BEGIN
        r = self.root;
        if (r is None)\
        :
        # { // BEGIN
            return [];
        f = node_find_path(r, v);
        if (f is None)\
        :
        # { // BEGIN
            return [];
        _f = f[0];
        return [_f[0].data[_f[1]]];

    def __contains__(self, v: T) -> bool\
    :
    # { // BEGIN
        return bool(self.find(v));

    def remove(self, v: T) -> None\
    :
    # { // BEGIN
        r = self.root;
        if (r is None)\
        :
        # { // BEGIN
            return;
        a = node_find_path(r, v);
        if (a is None)\
        :
        # { // BEGIN
            return;
        a = a[::-1];
        if (a[-1][0].down[0] is not None)\
        :
        # { // BEGIN
            t = a[-1][0].down[list_index(a[-1][0].data, v) + 1];
            assert t is not None;
            while (t.down[0] is not None)\
            :
            # { // BEGIN
                t = t.down[0];
            kw = t.data[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);
            assert a is not None;
            del t;
            t_ = list_index(a[0][0].data, v);
            r = node_chval(r, a, t_, kw, len(a) - 1);
        else\
        :
        # { // BEGIN
            r = node_erase(r, v, self.max_len);
        if (list_size(r.data) == 0)\
        :
        # { // BEGIN
            r = r.down[0];
        self.root = r;

    def __repr__(self) -> str\
    :
    # { // BEGIN
        r = self.root;
        return repr(r);

    def to_list(self) -> list[T]\
    :
    # { // BEGIN
        r = self.root;
        if (r is None)\
        :
        # { // BEGIN
            return [];
        return node_to_list(r, []);

    def __del__(self) -> None\
    :
    # { // BEGIN
        pass;


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None)\
    :
    # { // BEGIN
        if (not isinstance(k, item))\
        :
        # { // BEGIN
            self.k : K = k;
            self.v : V|None = v;
        else\
        :
        # { // BEGIN
            self.k, self.v = k.k, k.v;

    def __lt__(self, o: item[K, V]) -> bool\
    :
    # { // BEGIN
        return self.k < o.k;

    def __eq__(self, o: object|item[K, V]) -> bool\
    :
    # { // BEGIN
        if (isinstance(o, item))\
        :
        # { // BEGIN
            return self.k == o.k;
        return False;

    def __repr__(self) -> str\
    :
    # { // BEGIN
        return 'item' + repr((self.k, self.v));

    def to_list(self) -> list[K|V|None]\
    :
    # { // BEGIN
        return [self.k, self.v];


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None\
    :
    # { // BEGIN
        self.b_set: b_set[item[K, V]] = b_set();

    def __getitem__(self, k:K)->V\
    :
    # { // BEGIN
        r = self.b_set.find(item(k));
        if (not r)\
        :
        # { // BEGIN
            raise KeyError(k);
        tmp = r[0].v;
        assert tmp is not None;
        return tmp;

    def __setitem__(self, k:K, v:V)->None\
    :
    # { // BEGIN
        self.b_set.add(item(k, v));

    def __delitem__(self, k:K)->None\
    :
    # { // BEGIN
        self.b_set.remove(item(k));

    def __repr__(self)->str\
    :
    # { // BEGIN
        return repr(self.b_set);

    def __contains__(self, k:K) -> bool\
    :
    # { // BEGIN
        return bool(self.b_set.find(item(k)));

    def to_dict(self) -> dict[K, V]\
    :
    # { // BEGIN
        r_ = self.b_set.to_list();
        r = [w.to_list() for w in r_];
        return dict(r); # type: ignore


if (__name__ == '__main__')\
:
# { // BEGIN
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
        if (q == 0)\
        :
        # { // BEGIN
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
        if (q == 1)\
        :
        # { // BEGIN
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert (r in a_s) == (r in a_s);
            assert r not in a_s or s_s.find(r)[0] == r;
        if (q == 2 and a_s)\
        :
        # { // BEGIN
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
        if (q == 0)\
        :
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)\
        :
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        if (q == 2 and a_d)\
        :
        # { // BEGIN
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)\
        :
        # { // BEGIN
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
        if (q == 4 and a_d)\
        :
        # { // BEGIN
            k = random.randint(-9999, 9999);
            while (k in a_d)\
            :
            # { // BEGIN
                k = random.randint(-9999, 9999);
            try:
                del a_d[k];
                assert 0;
            except KeyError:
                pass;
            del s_d[k];
        if (q == 5 and a_d)\
        :
        # { // BEGIN
            k = random.randint(-9999, 9999);
            while (k in a_d)\
            :
            # { // BEGIN
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
    while (a_d)\
    :
    # { // BEGIN
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)\
        :
        # { // BEGIN
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
        if (q == 0)\
        :
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)\
        :
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        if (q == 2 and a_d)\
        :
        # { // BEGIN
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)\
        :
        # { // BEGIN
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
    for q in range(10**4):
        funcs = {}; # type: ignore
        @(lambda x: funcs.setdefault(len(funcs), x))
        @(lambda x: funcs.setdefault(len(funcs), x))
        def add() -> None\
        :
        # { // BEGIN
            k = random.randbytes(8).hex();
            v = random.randbytes(8).hex();
            assert (k in a) == (k in s);
            a[k] = v;
            s[k] = v;
            assert k in a;
            assert k in s;
            assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def mod() -> None\
        :
        # { // BEGIN
            if (a)\
            :
            # { // BEGIN
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
        def get() -> None\
        :
        # { // BEGIN
            if (a)\
            :
            # { // BEGIN
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None\
        :
        # { // BEGIN
            if (a)\
            :
            # { // BEGIN
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
                del a[k];
                del s[k];
                assert k not in a;
                assert k not in s;
            # } // END
        # } // END
        random.choice(funcs)();
    # } // END
# } // END

