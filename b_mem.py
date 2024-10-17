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

class List_(typing.Generic[T_]):
    def __init__(self, a: list[T_]|List_[T_]) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.l : list[T_];
        if (isinstance(a, list))// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert isinstance(a, list)
            self.l = a;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        elif (True)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert isinstance(a, List_)
            self.l = a.l;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        self.l = copy.copy(self.l);
    def __getitem__(self, i: int) -> T_:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        assert (0 <= i);
        return self.l.__getitem__(i);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    def __setitem__(self, i: int, v: T_) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        assert (0 <= i);
        return self.l.__setitem__(i, v);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_size(self: List_[T_]) -> int:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return self.l.__len__();
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_append(self: List_[T_], v: T_) -> None:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return self.l.append(v);
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_insert(self: List_[T_], i: int, v: T_) -> None:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return self.l.insert(i, v);
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_erase(self: List_[T_], i: int) -> T_:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return self.l.pop(i);
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_slice_assign(self: List_[T_], begin: int, end: int, val: list[T_]|List_[T_]) -> None:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    assert 0 <= begin <= end <= len(self.l)
    self.l[begin:end] = val if isinstance(val, list) else val.l;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_contains(self: List_[T_], val: T_) -> bool:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return val in self.l;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE
def list_index(self: List_[T_], v: T_) -> int:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return self.l.index(v);
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore




###################################################################################################################################


class node(typing.Generic[T]):
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    def __init__(self, *, data:List_[T], down: List_[node[T]|None]):
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.data = List_(data);
        self.down = List_(down);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_copy(self: node[T]) -> node[T]:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    return node(data=self.data, down=self.down);
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE


def node_insert(self: node[T]|None, elem: T, max_len: int) -> node[T]:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    assert (self is not None); # CPP_REMOVE
    assert (self != None);
    self = node_copy(self)
    if (list_contains(self.data, elem))// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        t = list_index(self.data, elem);
        self.data[t] = elem;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    elif (self.down[0] == None)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            w += 1;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        list_insert(self.data, w, elem);
        list_insert(self.down, 0, None);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    elif (True)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            w += 1;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        self.down[w] = node_insert(self.down[w], elem, max_len);
        tmp = self.down[w];
        assert (tmp is not None); # CPP_REMOVE
        assert (tmp != None);
        if (list_size(tmp.data) > max_len)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (list_size(tmp.data) == 1 + max_len);
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
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return self;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_find_path(self: node[T], elem: T) -> list[tuple[node[T], int]] | None:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    output : list[tuple[node[T], int]] = [];
    if (node_find_path_(self, elem, output))// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return output;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return None;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    (self);
    if (list_contains(self.data, elem))// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        output.append((self, list_index(self.data, (elem))));
        return True;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    if (self.down[0] == None)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return False;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    w = 0;
    while (w < list_size(self.data) and self.data[w] < elem)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        w += 1;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    tmp = self.down[w];
    assert (tmp is not None); # CPP_REMOVE
    assert (tmp != None);
    if (node_find_path_(tmp, elem, output))// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        output.append((self, w));
        return True;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return False;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_erase(self: node[T], elem: T, max_len: int) -> node[T]:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    (self);
    t: None|node[T];
    self = node_copy(self);
    if (self.down[0] == None)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        t_ = list_index(self.data, (elem));
        list_erase(self.data, t_);
        list_erase(self.down, 0);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    elif (True)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        w = 0;
        while (w < list_size(self.data) and self.data[w] < elem)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            w += 1;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        tmp = self.down[w];
        assert (tmp is not None); # CPP_REMOVE
        assert (tmp != None);
        self.down[w] = node_erase(tmp, elem, max_len);
        tmp = self.down[w];
        assert (tmp is not None); # CPP_REMOVE
        assert (tmp != None);
        if (list_size(tmp.data) <x__div( max_len ,  2))// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (list_size(tmp.data) ==x__div( max_len ,  2) - 1);
            if (w)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                e = w - 1;
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            elif (True)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                e = w + 1;
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            q = max(w, e);
            r = min(w, e);
            tmp = self.down[e];
            assert (tmp is not None); # CPP_REMOVE
            assert (tmp != None);
            if (list_size(tmp.data) ==x__div( max_len ,  2))// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                tmp = self.down[q];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                t = node_copy(tmp);
                tmp = self.down[r];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                __t = tmp.data;
                list_append(__t, self.data[r]);
                list_slice_assign(t.data, 0, 0, __t);
                tmp = self.down[r];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                list_slice_assign(t.down, 0,0,tmp.down);
                list_slice_assign(self.down, r,q + 1, [t]); # type: ignore
                list_slice_assign(self.data, r,q , []);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            elif (True)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                tmp = self.down[w];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                t = node_copy(tmp);
                l = (q - w) * list_size(t.down);
                tmp_1 = l
                if (tmp_1 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_1 += list_size(t.data)
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                if (tmp_1 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_1 = 0
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                if (tmp_1 > list_size(t.data))// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_1 = list_size(t.data)
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                list_slice_assign(t.data, tmp_1, tmp_1, [self.data[r]]);
                tmp = self.down[e];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                tmp_1 = l
                list_slice_assign(t.down, tmp_1, tmp_1, [tmp.down[(e - q + list_size(tmp.down)) % list_size(tmp.down)]]);
                self.down[w] = t;
                tmp = self.down[e];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                self.data[r] = tmp.data[(e - q + list_size(tmp.data)) % list_size(tmp.data)];
                tmp = self.down[e];
                assert (tmp is not None); # CPP_REMOVE
                assert (tmp != None);
                t = node_copy(tmp);
                tmp_1 = e - q
                if (tmp_1 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_1 += list_size(t.data);
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                tmp_2 = list_size(t.data) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_2 += list_size(t.data)
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                list_slice_assign(t.data, tmp_1, tmp_2, []);
                tmp_1 = e - q
                if (tmp_1 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_1 += list_size(t.down);
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                tmp_2 = list_size(t.down) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                    ''' # CPP_REMOVE
                    { // BEGIN
                    ''' # CPP_REMOVE
                    tmp_2 += list_size(t.data)
                    ''' # CPP_REMOVE
                    } // END
                    ''' # CPP_REMOVE
                list_slice_assign(t.down, tmp_1, tmp_2, []);
                self.down[e] = t;
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return self;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_to_list(self: node[T], l: list[T]) -> list[T]:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    if (self.down[0] == None)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        i_ = 0
        while i_ < list_size(self.data):
            w_ = self.data[i_];
            l.append(w_);
            i_ += 1
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    elif (True)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        tmp = self.down[0]
        assert (tmp != None)
        assert (tmp is not None) # CPP_REMOVE
        node_to_list(tmp, l);
        i_ = 0
        while i_ < list_size(self.data):
            w = i_
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            l.append(self.data[w]);
            tmp = self.down[w + 1];
            assert (isinstance(tmp, node));
            node_to_list(tmp, l);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
            i_ += 1
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return l;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

def node_chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE
    self = node_copy(self);
    if (n)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        v = a[n][1];
        tmp = self.down[v];
        assert (tmp is not None); # CPP_REMOVE
        assert (tmp != None);
        self.down[v] = node_chval(tmp, a, t, kw, n - 1);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    elif (True)// simple():
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        assert (self.data != None);
        assert (isinstance(t, int));
        self.data[t] = kw;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    return self;
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE


Node = node[T] | None;


class b_set(typing.Generic[T]):

    def __init__(self) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.root: Node[T] = None;
        self.max_len = 99;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def add(self, v: T) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        q = node(data=List_([]), down=List_([self.root, ]));
        q = node_insert(q, v, self.max_len);
        if (not list_size(q.data))// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            tmp = q.down[0];
            assert (tmp is not None); # CPP_REMOVE
            assert (tmp != None);
            q = tmp;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        self.root = q;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def find(self, v: T) -> list[T]:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r = self.root;
        if (r == None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            return [];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        assert (r != None)
        assert (r is not None) # CPP_REMOVE
        f = node_find_path(r, v);
        if (f == None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            return [];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        assert (f != None)
        assert (f is not None) # CPP_REMOVE
        _f = f[0];
        return [_f[0].data[_f[1]]];
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __contains__(self, v: T) -> bool:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return bool(self.find(v));
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def remove(self, v: T) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r = self.root;
        if (r == None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            return;
        assert (r != None)
        assert (r is not None) # CPP_REMOVE
        a = node_find_path(r, v);
        if (a == None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            return;
        assert (a != None)
        assert (a is not None) # CPP_REMOVE
        a = a[::-1];
        if (a[-1][0].down[0] != None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            t = a[-1][0].down[list_index(a[-1][0].data, v) + 1];
            assert (t is not None); # CPP_REMOVE
            assert (t != None);
            while (t.down[0] != None)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                t = t.down[0];
                assert (t is not None); # CPP_REMOVE
                assert (t != None);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            kw = t.data[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);
            assert (a is not None); # CPP_REMOVE
            assert (a != None);
            del t;
            t_ = list_index(a[0][0].data, v);
            r = node_chval(r, a, t_, kw, len(a) - 1);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        elif (True)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            r = node_erase(r, v, self.max_len);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (list_size(r.data) == 0)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            r = r.down[0];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        self.root = r;

    def __repr__(self) -> str:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r = self.root;
        return repr(r);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def to_list(self) -> list[T]:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r = self.root;
        if (r == None)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            return [];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        assert (r is not None); # CPP_REMOVE
        assert (r != None);
        return node_to_list(r, []);

    def __del__(self) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        pass;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None):
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        if (not isinstance(k, item))// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (not isinstance(k, item));
            self.k : K = k;
            self.v : V|None = v;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        elif (True)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (isinstance(k, item));
            self.k, self.v = k.k, k.v;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE

    def __lt__(self, o: item[K, V]) -> bool:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return self.k < o.k;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __eq__(self, o: object|item[K, V]) -> bool:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        if (isinstance(o, item))// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (isinstance(o, item));
            return self.k == o.k;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        return False;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __repr__(self) -> str:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return 'item' + repr((self.k, self.v));
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def to_list(self) -> list[K|V|None]:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return [self.k, self.v];
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.b_set: b_set[item[K, V]] = b_set();
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __getitem__(self, k:K)->V:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r = self.b_set.find(item(k));
        if (not r)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            raise KeyError(k);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        tmp = r[0].v;
        assert (tmp is not None); # CPP_REMOVE
        assert (tmp != None);
        return tmp;
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __setitem__(self, k:K, v:V)->None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.b_set.add(item(k, v));
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __delitem__(self, k:K)->None:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        self.b_set.remove(item(k));
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __repr__(self)->str:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return repr(self.b_set);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def __contains__(self, k:K) -> bool:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        return bool(self.b_set.find(item(k)));
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    def to_dict(self) -> dict[K, V]:
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        r_:list[item[K, V]] = self.b_set.to_list();
        r:List_[item[K, V]] = List_([])
        i_ = 0
        while i_ < len(r_):
            w = r_[i_]
            e = w.to_list()
            list_append(r, e) # type: ignore
            i_ += 1
        # r = [w.to_list() for w in r_];
        return dict(r); # type: ignore
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE


if (__name__ == '__main__')// simple():
    ''' # CPP_REMOVE
    { // BEGIN
    ''' # CPP_REMOVE

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
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 1)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert ((r in a_s) == (r in a_s));
            assert (r not in a_s or s_s.find(r)[0] == r);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 2 and a_s)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        f = set(s_s.to_list());
        assert (a_s == f);
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE

    print([time.time()-t,(t:=time.time())][0]);


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 1)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 2 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 3 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        if (q == 4 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                k = random.randint(-9999, 9999);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            try:
                del a_d[k];
                assert (0);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            except KeyError:
                pass;
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            del s_d[k];
        if (q == 5 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                k = random.randint(-9999, 9999);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            try:
                a_d[k];
                assert (0);
            except KeyError:
                pass;
            try:
                s_d[k];
                assert (0);
            except KeyError:
                pass;
        assert (s_d.to_dict() == a_d);

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
        ''' # CPP_REMOVE
        { // BEGIN
        ''' # CPP_REMOVE
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            assert (s_d.to_dict() == a_d);
    assert (s_d.to_dict() == a_d);

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
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
        if (q == 2 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)// simple():
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
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
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            k = random.randbytes(8).hex();
            v = random.randbytes(8).hex();
            assert ((k in a) == (k in s));
            a[k] = v;
            s[k] = v;
            assert (k in a);
            assert (k in s);
            assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def mod() -> None:
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            if (a)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                k = random.choice([*a.keys()]);
                v = random.randbytes(8).hex();
                assert (k in a);
                assert (k in s);
                a[k] = v;
                s[k] = v;
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def get() -> None:
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            if (a)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
            ''' # CPP_REMOVE
            { // BEGIN
            ''' # CPP_REMOVE
            if (a)// simple():
                ''' # CPP_REMOVE
                { // BEGIN
                ''' # CPP_REMOVE
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
                del a[k];
                del s[k];
                assert (k not in a);
                assert (k not in s);
                ''' # CPP_REMOVE
                } // END
                ''' # CPP_REMOVE
            ''' # CPP_REMOVE
            } // END
            ''' # CPP_REMOVE
        random.choice(funcs)();
        ''' # CPP_REMOVE
        } // END
        ''' # CPP_REMOVE
    ''' # CPP_REMOVE
    } // END
    ''' # CPP_REMOVE

