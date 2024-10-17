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

class simple:
    def __rfloordiv__(self, o: T_) -> T_:
        return o

def x__div(a: T_, b: T_) -> T_:
    a = a // b # type: ignore
    return a

class List(typing.Generic[T_]):
    def __init__(self, a: list[T_]|List[T_]) -> None:
    # { // BEGIN
        self.l : list[T_];
        if (isinstance(a, list))// simple():
        # { // BEGIN
            assert isinstance(a, list)
            self.l = a;
        # } // END
        elif (True)// simple():
        # { // BEGIN
            assert isinstance(a, List)
            self.l = a.l;
        # } // END
        self.l = copy.copy(self.l);
    def __getitem__(self, i: int) -> T_:
    # { // BEGIN
        assert 0 <= i;
        return self.l.__getitem__(i);
    # } // END
    def __setitem__(self, i: int, v: T_) -> None:
    # { // BEGIN
        assert 0 <= i;
        return self.l.__setitem__(i, v);
    # } // END
# } // END
def list_size(self: List[T_]) -> int:
#00 { // BEGIN
    return self.l.__len__();
#00 } // END
def list_append(self: List[T_], v: T_) -> None:
#00 { // BEGIN
    return self.l.append(v);
#00 } // END
def list_insert(self: List[T_], i: int, v: T_) -> None:
#00 { // BEGIN
    return self.l.insert(i, v);
#00 } // END
def list_erase(self: List[T_], i: int) -> T_:
#00 { // BEGIN
    return self.l.pop(i);
#00 } // END
def list_slice_assign(self: List[T_], begin: int, end: int, val: list[T_]|List[T_]) -> None:
#00 { // BEGIN
    assert 0 <= begin <= end <= len(self.l)
    self.l[begin:end] = val if isinstance(val, list) else val.l;
#00 } // END
def list_contains(self: List[T_], val: T_) -> bool:
#00 { // BEGIN
    return val in self.l;
#00 } // END
def list_index(self: List[T_], v: T_) -> int:
#00 { // BEGIN
    return self.l.index(v);
#00 } // END

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore

class node(typing.Generic[T]):
# { // BEGIN
    def __init__(self, *, data:List[T], down: List[node[T]|None]):
    # { // BEGIN
        self.data = List(data);
        self.down = List(down);
    # } // END
# } // END

def node_copy(self: node[T]) -> node[T]:
#00 { // BEGIN
    return node(data=self.data, down=self.down);
#00 } // END


def node_insert(self: node[T]|None, elem: T, max_len: int) -> node[T]:
#00 { // BEGIN
    (self);
    assert self is not None;
    self = node_copy(self)
    if (list_contains(self.data, elem))// simple():
    #01 { // BEGIN
        t = list_index(self.data, elem);
        self.data[t] = elem;
    #01 } // END
    elif (self.down[0] is None)// simple():
    #01 { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
        #02 { // BEGIN
            w += 1;
        #02 } // END
        list_insert(self.data, w, elem);
        list_insert(self.down, 0, None);
    #01 } // END
    elif (True)// simple():
    #01 { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
        #02 { // BEGIN
            w += 1;
        #02 } // END
        self.down[w] = node_insert(self.down[w], elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) > max_len)// simple():
        #02 { // BEGIN
            assert list_size(tmp.data) == 1 + max_len;
            q = node_copy(tmp);
            a = node_copy(q);
            list_slice_assign(a.data,x__div( max_len ,  2),list_size(a.data), []);
            list_slice_assign(a.down,x__div( max_len ,  2) + 1,list_size(a.down),[]);
            kw = q.data[x__div(max_len ,  2)];
            list_slice_assign(q.data, 0,x__div( max_len ,  2) + 1, []);
            list_slice_assign(q.down, 0,x__div(max_len ,  2) + 1, []);
            list_insert(self.data, w, kw);
            self.down[w] = q;
            list_insert(self.down, w, a);
        #02 } // END
    #01 } // END
    return self;
#00 } // END

def node_find_path(self: node[T], elem: T) -> list[tuple[node[T], int]] | None:
#00 { // BEGIN
    output : list[tuple[node[T], int]] = [];
    if (node_find_path_(self, elem, output))// simple():
    #01 { // BEGIN
        return output;
    #01 } // END
    return None;
#00 } // END

def node_find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool:
#00 { // BEGIN
    (self);
    if (list_contains(self.data, elem))// simple():
    #01 { // BEGIN
        output.append((self, list_index(self.data, (elem))));
        return True;
    #01 } // END
    if (self.down[0] is None)// simple():
    #01 { // BEGIN
        return False;
    #01 } // END
    w = 0;
    while (w < list_size(self.data) and self.data[w] < elem)// simple():
    #01 { // BEGIN
        w += 1;
    #01 } // END
    tmp = self.down[w];
    assert tmp is not None;
    if (node_find_path_(tmp, elem, output))// simple():
    #01 { // BEGIN
        output.append((self, w));
        return True;
    #01 } // END
    return False;
#00 } // END

def node_erase(self: node[T], elem: T, max_len: int) -> node[T]:
#00 { // BEGIN
    (self);
    t: None|node[T];
    self = node_copy(self);
    if (self.down[0] is None)// simple():
    #01 { // BEGIN
        t_ = list_index(self.data, (elem));
        list_erase(self.data, t_);
        list_erase(self.down, 0);
    #01 } // END
    elif (True)// simple():
    #01 { // BEGIN
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
        #02 { // BEGIN
            w += 1;
        #02 } // END
        tmp = self.down[w];
        assert tmp is not None;
        self.down[w] = node_erase(tmp, elem, max_len);
        tmp = self.down[w];
        assert tmp is not None;
        if (list_size(tmp.data) <x__div( max_len ,  2))// simple():
        #02 { // BEGIN
            assert list_size(tmp.data) ==x__div( max_len ,  2) - 1;
            if (w)// simple():
            #03 { // BEGIN
                e = w - 1;
            #03 } // END
            elif (True)// simple():
            # { // BEGIN
                e = w + 1;
            # } // END
            q = max(w, e);
            r = min(w, e);
            tmp = self.down[e];
            assert tmp is not None;
            if (list_size(tmp.data) ==x__div( max_len ,  2))// simple():
            #03 { // BEGIN
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
            #03 } // END
            elif (True)// simple():
            #03 { // BEGIN
                tmp = self.down[w];
                assert tmp is not None;
                t = node_copy(tmp);
                l = (q - w) * list_size(t.down);
                tmp_1 = l
                if (tmp_1 < 0)// simple():
                #04 { // BEGIN
                    tmp_1 += list_size(t.data)
                #04 } // END
                if (tmp_1 < 0)// simple():
                #04 { // BEGIN
                    tmp_1 = 0
                #04 } // END
                if (tmp_1 > list_size(t.data))// simple():
                #04 { // BEGIN
                    tmp_1 = list_size(t.data)
                #04 } // END
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
                if (tmp_1 < 0)// simple():
                #04 { // BEGIN
                    tmp_1 += list_size(t.data);
                #04 } // END
                tmp_2 = list_size(t.data) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                #04 { // BEGIN
                    tmp_2 += list_size(t.data)
                #04 } // END
                list_slice_assign(t.data, tmp_1, tmp_2, []);
                tmp_1 = e - q
                if (tmp_1 < 0)// simple():
                #04 { // BEGIN
                    tmp_1 += list_size(t.down);
                #04 } // END
                tmp_2 = list_size(t.down) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                #04 { // BEGIN
                    tmp_2 += list_size(t.data)
                #04 } // END
                list_slice_assign(t.down, tmp_1, tmp_2, []);
                self.down[e] = t;
            #03 } // END
        #02 } // END
    #01 } // END
    return self;
#00 } // END

def node_to_list(self: node[T], l: list[T]) -> list[T]:
#00 { // BEGIN
    if (self.down[0] is None)// simple():
    #01 { // BEGIN
        for i_ in range(list_size(self.data)):
            w_ = self.data[i_];
            l.append(w_);
    #01 } // END
    elif (True)// simple():
    #01 { // BEGIN
        tmp = self.down[0]
        assert tmp is not None
        node_to_list(tmp, l);
        for w in range(list_size(self.data)):
        #03 { // BEGIN
            l.append(self.data[w]);
            tmp = self.down[w + 1];
            assert isinstance(tmp, node);
            node_to_list(tmp, l);
        #03 } // END
    #01 } // END
    return l;
#00 } // END

def node_chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
#00 { // BEGIN
    self = node_copy(self);
    if (n)// simple():
    #01 { // BEGIN
        v = a[n][1];
        tmp = self.down[v];
        assert tmp is not None;
        self.down[v] = node_chval(tmp, a, t, kw, n - 1);
    #01 } // END
    elif (True)// simple():
    #01 { // BEGIN
        assert self.data is not None;
        assert isinstance(t, int);
        self.data[t] = kw;
    #01 } // END
    return self;
#00 } // END


Node = node[T] | None;


class b_set(typing.Generic[T]):

    def __init__(self) -> None:
    #01 { // BEGIN
        self.root: Node[T] = None;
        self.max_len = 99;
    #01 } // END

    def add(self, v: T) -> None:
    #01 { // BEGIN
        q = node(data=List([]), down=List([self.root, ]));
        q = node_insert(q, v, self.max_len);
        if (not list_size(q.data))// simple():
        #03 { // BEGIN
            tmp = q.down[0];
            assert tmp is not None;
            q = tmp;
        #03 } // END
        self.root = q;
    #01 } // END

    def find(self, v: T) -> list[T]:
    #01 { // BEGIN
        r = self.root;
        if (r is None)// simple():
        #03 { // BEGIN
            return [];
        #03 } // END
        assert r is not None
        f = node_find_path(r, v);
        if (f is None)// simple():
        #03 { // BEGIN
            return [];
        #03 } // END
        assert f is not None
        _f = f[0];
        return [_f[0].data[_f[1]]];
    #01 } // END

    def __contains__(self, v: T) -> bool:
    #01 { // BEGIN
        return bool(self.find(v));
    #01 } // END

    def remove(self, v: T) -> None:
    # { // BEGIN
        r = self.root;
        if (r is None)// simple():
        # { // BEGIN
            return;
        assert r is not None
        a = node_find_path(r, v);
        if (a is None)// simple():
        # { // BEGIN
            return;
        assert a is not None
        a = a[::-1];
        if (a[-1][0].down[0] is not None)// simple():
        #03 { // BEGIN
            t = a[-1][0].down[list_index(a[-1][0].data, v) + 1];
            assert t is not None;
            while (t.down[0] is not None)// simple():
            #04 { // BEGIN
                t = t.down[0];
                assert t is not None;
            #04 } // END
            kw = t.data[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);
            assert a is not None;
            del t;
            t_ = list_index(a[0][0].data, v);
            r = node_chval(r, a, t_, kw, len(a) - 1);
        #03 } // END
        elif (True)// simple():
        #03 { // BEGIN
            r = node_erase(r, v, self.max_len);
        #03 } // END
        if (list_size(r.data) == 0)// simple():
        #03 { // BEGIN
            r = r.down[0];
        #03 } // END
        self.root = r;

    def __repr__(self) -> str:
    #01 { // BEGIN
        r = self.root;
        return repr(r);
    #01 } // END

    def to_list(self) -> list[T]:
    # { // BEGIN
        r = self.root;
        if (r is None)// simple():
        #03 { // BEGIN
            return [];
        #03 } // END
        assert r is not None;
        return node_to_list(r, []);

    def __del__(self) -> None:
    #01 { // BEGIN
        pass;
    #01 } // END
#00 } // END


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None):
    # { // BEGIN
        if (not isinstance(k, item))// simple():
        #03 { // BEGIN
            assert not isinstance(k, item);
            self.k : K = k;
            self.v : V|None = v;
        #03 } // END
        elif (True)// simple():
        #03 { // BEGIN
            assert isinstance(k, item);
            self.k, self.v = k.k, k.v;
        #03 } // END

    def __lt__(self, o: item[K, V]) -> bool:
    #01 { // BEGIN
        return self.k < o.k;
    #01 } // END

    def __eq__(self, o: object|item[K, V]) -> bool:
    #01 { // BEGIN
        if (isinstance(o, item))// simple():
        #03 { // BEGIN
            assert isinstance(o, item);
            return self.k == o.k;
        #03 } // END
        return False;
    #01 } // END

    def __repr__(self) -> str:
    #01 { // BEGIN
        return 'item' + repr((self.k, self.v));
    #01 } // END

    def to_list(self) -> list[K|V|None]:
    #01 { // BEGIN
        return [self.k, self.v];
    #01 } // END


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
    #01 { // BEGIN
        self.b_set: b_set[item[K, V]] = b_set();
    #01 } // END

    def __getitem__(self, k:K)->V:
    #01 { // BEGIN
        r = self.b_set.find(item(k));
        if (not r)// simple():
        #03 { // BEGIN
            raise KeyError(k);
        #03 } // END
        tmp = r[0].v;
        assert tmp is not None;
        return tmp;
    #01 } // END

    def __setitem__(self, k:K, v:V)->None:
    #01 { // BEGIN
        self.b_set.add(item(k, v));
    #01 } // END

    def __delitem__(self, k:K)->None:
    #01 { // BEGIN
        self.b_set.remove(item(k));
    #01 } // END

    def __repr__(self)->str:
    #01 { // BEGIN
        return repr(self.b_set);
    #01 } // END

    def __contains__(self, k:K) -> bool:
    #01 { // BEGIN
        return bool(self.b_set.find(item(k)));
    #01 } // END

    def to_dict(self) -> dict[K, V]:
    #01 { // BEGIN
        r_ = self.b_set.to_list();
        r = [w.to_list() for w in r_];
        return dict(r); # type: ignore
    #01 } // END


if (__name__ == '__main__')// simple():
#00 { // BEGIN

    t=time.time();
    print([time.time()-t,(t:=time.time())][0]);

    sed = random.randint(-9999, 9999);
    print(sed);
    random.seed(sed);
    s_s: b_set[int] = b_set();
    a_s = set();
    for w in range(99):
        q = random.choice([0] * 3 + [1] + [2]);
        if (q == 0)// simple():
        # { // BEGIN
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
        # } // END
        if (q == 1)// simple():
        # { // BEGIN
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert (r in a_s) == (r in a_s);
            assert r not in a_s or s_s.find(r)[0] == r;
        # } // END
        if (q == 2 and a_s)// simple():
        # { // BEGIN
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
        # } // END
        f = set(s_s.to_list());
        assert a_s == f;
    # } // END

    print([time.time()-t,(t:=time.time())][0]);


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
    # { // BEGIN
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0)// simple():
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        # } // END
        if (q == 1)// simple():
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        # } // END
        if (q == 2 and a_d)// simple():
        # { // BEGIN
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        # } // END
        if (q == 3 and a_d)// simple():
        # { // BEGIN
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
        # } // END
        if (q == 4 and a_d)// simple():
        # { // BEGIN
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
            # { // BEGIN
                k = random.randint(-9999, 9999);
            # } // END
            try:
                del a_d[k];
                assert 0;
            # } // END
            except KeyError:
                pass;
            # } // END
            del s_d[k];
        if (q == 5 and a_d)// simple():
        # { // BEGIN
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
            # { // BEGIN
                k = random.randint(-9999, 9999);
            # } // END
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

    print([time.time()-t,(t:=time.time())][0]);

    a_d = dict();
    s_d = b_dict();
    for w in range(199):
        k = random.randint(-9999, 9999);
        v = random.randint(-9999, 9999);
        s_d[k] = v;
        a_d[k] = v;


    print([time.time()-t,(t:=time.time())][0]);

    w = 0;
    while (a_d)// simple():
    # { // BEGIN
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)// simple():
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
        if (q == 0)// simple():
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)// simple():
        # { // BEGIN
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert (k in a_d) == (k in s_d);
        if (q == 2 and a_d)// simple():
        # { // BEGIN
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)// simple():
        # { // BEGIN
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];

    print([time.time()-t,(t:=time.time())][0]);

    print([time.time()-t,(t:=time.time())][0]);

    a :   dict[str, str] = dict();
    s : b_dict[str, str] = b_dict();
    for q in range(10**4):
        funcs = {}; # type: ignore
        @(lambda x: funcs.setdefault(len(funcs), x))
        @(lambda x: funcs.setdefault(len(funcs), x))
        def add() -> None:
        #02 { // BEGIN
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
        # { // BEGIN
            if (a)// simple():
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
        def get() -> None:
        # { // BEGIN
            if (a)// simple():
            # { // BEGIN
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
        #02 { // BEGIN
            if (a)// simple():
            #03 { // BEGIN
                k = random.choice([*a.keys()]);
                assert k in a;
                assert k in s;
                assert a[k] == s[k];
                del a[k];
                del s[k];
                assert k not in a;
                assert k not in s;
            #03 } // END
        #02 } // END
        random.choice(funcs)();
    #02 } // END
#00 } // END

