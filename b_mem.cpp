#define COMBINE1(X,Y) X##Y
#define COMBINE(X,Y) COMBINE1(X,Y)
#define UNIQUE_IDENTIFIER COMBINE(const char* x__,__LINE__)

#define aaaaa aaaa\
from __future__ import annotations

UNIQUE_IDENTIFIER = """_"/*""";


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
        self.l : list[T_];
        if (isinstance(a, list))// simple():
            assert isinstance(a, list)
            self.l = a;
        elif (True)// simple():
            assert isinstance(a, List_)
            self.l = a.l;
        self.l = copy.copy(self.l);
    def __getitem__(self, i: int) -> T_:
        assert (0 <= i);
        return self.l.__getitem__(i);
    def __setitem__(self, i: int, v: T_) -> None:
        assert (0 <= i);
        return self.l.__setitem__(i, v);
def list_size(self: List_[T_]) -> int:
    return self.l.__len__();
def list_append(self: List_[T_], v: T_) -> None:
    return self.l.append(v);
def list_insert(self: List_[T_], i: int, v: T_) -> None:
    return self.l.insert(i, v);
def list_erase(self: List_[T_], i: int) -> T_:
    return self.l.pop(i);
def list_slice_assign(self: List_[T_], begin: int, end: int, val: list[T_]|List_[T_]) -> None:
    assert 0 <= begin <= end <= len(self.l)
    self.l[begin:end] = val if isinstance(val, list) else val.l;
def list_contains(self: List_[T_], val: T_) -> bool:
    return val in self.l;
def list_index(self: List_[T_], v: T_) -> int:
    return self.l.index(v);

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore

###################################################################################################################################

UNIQUE_IDENTIFIER = """*/"_""";

# define True true
# define False false
# define None nullptr

UNIQUE_IDENTIFIER = """_"/*""";
''' 
UNIQUE_IDENTIFIER = """*/"_""";

#include <vector>
#include <memory>
#include <cinttypes>
#include <cstdint>
template<typename T>
struct node_s{
    std::vector<T> data;
    std::vector<std::shared_ptr<node_s>> down;
};

template<typename T>
struct node{
    std::shared_ptr<std::vector<node_s<T>>> data_;
    auto& data(){
        return data_->data;
    }
    auto& down(){
        return data_->down;
    }
};

template<typename T>
node<T> node_copy(node<T> self){
    return node{make_shared<node_s<T>>(*self.data_)};
}

UNIQUE_IDENTIFIER = """_"/*""";
''' 
class node(typing.Generic[T]):
    def __init__(self, *, data:List_[T], down: List_[node[T]|None]):
        self.data_ = List_(data);
        self.down_ = List_(down);
    def data(self) -> List_[T]:
        return self.data_
    def down(self) -> List_[node[T]|None]:
        return self.down_

def node_copy(self: node[T]) -> node[T]:
    return node(data=self.data(), down=self.down());

def node_insert(self: node[T]|None, elem: T, max_len: int) -> node[T]:
    '''
    UNIQUE_IDENTIFIER = """*/"_""";
template<typename T>
auto node_insert(node<T> self, T&& elem, int64_t max_len) -> node<T>{
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    assert (self is not None); 
    UNIQUE_IDENTIFIER = """*/"_""";
    assert (self != None);
    self = node_copy(self);
    if (list_contains(self.data(), elem))// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        int64_t
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        t = list_index(self.data(), elem);
        self.data()[t] = elem;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    elif (self.down()[0] == None)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            w += 1;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        list_insert(self.data(), w, elem);
        list_insert(self.down(), 0, None);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    elif (True)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            w += 1;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        self.down()[w] = node_insert(self.down()[w], elem, max_len);
        tmp = self.down()[w];
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (tmp != None);
        if (list_size(tmp.data()) > max_len)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (list_size(tmp.data()) == 1 + max_len);
            q = node_copy(tmp);
            a = node_copy(q);
            list_slice_assign(a.data(),x__div( max_len ,  2),list_size(a.data()), []);
            list_slice_assign(a.down(),x__div( max_len ,  2) + 1,list_size(a.down()),[]);
            kw = q.data()[x__div(max_len ,  2)];
            list_slice_assign(q.data(), 0,x__div( max_len ,  2) + 1, []);
            list_slice_assign(q.down(), 0,x__div(max_len ,  2) + 1, []);
            list_insert(self.data(), w, kw);
            self.down()[w] = q;
            list_insert(self.down(), w, a);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return self;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

def node_find_path(self: node[T], elem: T) -> list[tuple[node[T], int]] | None:
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    output : list[tuple[node[T], int]] = [];
    if (node_find_path_(self, elem, output))// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return output;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return None;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

def node_find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool:
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    (self);
    if (list_contains(self.data(), elem))// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        output.append((self, list_index(self.data(), (elem))));
        return True;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    if (self.down()[0] == None)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return False;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    w = 0;
    while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        w += 1;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    tmp = self.down()[w];
    UNIQUE_IDENTIFIER = """_"/*""";
    assert (tmp is not None); 
    UNIQUE_IDENTIFIER = """*/"_""";
    assert (tmp != None);
    if (node_find_path_(tmp, elem, output))// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        output.append((self, w));
        return True;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return False;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

def node_erase(self: node[T], elem: T, max_len: int) -> node[T]:
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    (self);
    t: None|node[T];
    self = node_copy(self);
    if (self.down()[0] == None)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        t_ = list_index(self.data(), (elem));
        list_erase(self.data(), t_);
        list_erase(self.down(), 0);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    elif (True)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            w += 1;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        tmp = self.down()[w];
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (tmp != None);
        self.down()[w] = node_erase(tmp, elem, max_len);
        tmp = self.down()[w];
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (tmp != None);
        if (list_size(tmp.data()) <x__div( max_len ,  2))// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (list_size(tmp.data()) ==x__div( max_len ,  2) - 1);
            if (w)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                e = w - 1;
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            elif (True)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                e = w + 1;
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            q = max(w, e);
            r = min(w, e);
            tmp = self.down()[e];
            UNIQUE_IDENTIFIER = """_"/*""";
            assert (tmp is not None); 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (tmp != None);
            if (list_size(tmp.data()) ==x__div( max_len ,  2))// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                tmp = self.down()[q];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                t = node_copy(tmp);
                tmp = self.down()[r];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                __t = tmp.data();
                list_append(__t, self.data()[r]);
                list_slice_assign(t.data(), 0, 0, __t);
                tmp = self.down()[r];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                list_slice_assign(t.down(), 0,0,tmp.down());
                list_slice_assign(self.down(), r,q + 1, [t]); # type: ignore
                list_slice_assign(self.data(), r,q , []);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            elif (True)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                tmp = self.down()[w];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                t = node_copy(tmp);
                l = (q - w) * list_size(t.down());
                tmp_1 = l
                if (tmp_1 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_1 += list_size(t.data())
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                if (tmp_1 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_1 = 0
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                if (tmp_1 > list_size(t.data()))// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_1 = list_size(t.data())
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                list_slice_assign(t.data(), tmp_1, tmp_1, [self.data()[r]]);
                tmp = self.down()[e];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                tmp_1 = l
                list_slice_assign(t.down(), tmp_1, tmp_1, [tmp.down()[(e - q + list_size(tmp.down())) % list_size(tmp.down())]]);
                self.down()[w] = t;
                tmp = self.down()[e];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                self.data()[r] = tmp.data()[(e - q + list_size(tmp.data())) % list_size(tmp.data())];
                tmp = self.down()[e];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (tmp is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (tmp != None);
                t = node_copy(tmp);
                tmp_1 = e - q
                if (tmp_1 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_1 += list_size(t.data());
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                tmp_2 = list_size(t.data()) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_2 += list_size(t.data())
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                list_slice_assign(t.data(), tmp_1, tmp_2, []);
                tmp_1 = e - q
                if (tmp_1 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_1 += list_size(t.down());
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                tmp_2 = list_size(t.down()) * (q - e) + (q - w)
                if (tmp_2 < 0)// simple():
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    { // BEGIN
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    tmp_2 += list_size(t.data())
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                    } // END
                    UNIQUE_IDENTIFIER = """_"/*""";
                    ''' 
                    UNIQUE_IDENTIFIER = """*/"_""";
                list_slice_assign(t.down(), tmp_1, tmp_2, []);
                self.down()[e] = t;
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return self;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

def node_to_list(self: node[T], l: list[T]) -> list[T]:
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    if (self.down()[0] == None)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        i_ = 0
        while i_ < list_size(self.data()):
            w_ = self.data()[i_];
            l.append(w_);
            i_ += 1
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    elif (True)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        tmp = self.down()[0]
        assert (tmp != None)
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None) 
        UNIQUE_IDENTIFIER = """*/"_""";
        node_to_list(tmp, l);
        i_ = 0
        while i_ < list_size(self.data()):
            w = i_
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            l.append(self.data()[w]);
            tmp = self.down()[w + 1];
            assert (isinstance(tmp, node));
            node_to_list(tmp, l);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            i_ += 1
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return l;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

def node_chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    self = node_copy(self);
    if (n)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        v = a[n][1];
        tmp = self.down()[v];
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (tmp != None);
        self.down()[v] = node_chval(tmp, a, t, kw, n - 1);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    elif (True)// simple():
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (self.data() != None);
        assert (isinstance(t, int));
        self.data()[t] = kw;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    return self;
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";


Node = node[T] | None;


class b_set(typing.Generic[T]):

    def __init__(self) -> None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        self.root: Node[T] = None;
        self.max_len = 99;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def add(self, v: T) -> None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        q = node(data=List_([]), down=List_([self.root, ]));
        q = node_insert(q, v, self.max_len);
        if (not list_size(q.data()))// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            tmp = q.down()[0];
            UNIQUE_IDENTIFIER = """_"/*""";
            assert (tmp is not None); 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (tmp != None);
            q = tmp;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        self.root = q;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def find(self, v: T) -> list[T]:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        r = self.root;
        if (r == None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            return [];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        assert (r != None)
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (r is not None) 
        UNIQUE_IDENTIFIER = """*/"_""";
        f = node_find_path(r, v);
        if (f == None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            return [];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        assert (f != None)
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (f is not None) 
        UNIQUE_IDENTIFIER = """*/"_""";
        _f = f[0];
        return [_f[0].data()[_f[1]]];
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __contains__(self, v: T) -> bool:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return bool(self.find(v));
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def remove(self, v: T) -> None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        r = self.root;
        if (r == None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            return;
        assert (r != None)
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (r is not None) 
        UNIQUE_IDENTIFIER = """*/"_""";
        a = node_find_path(r, v);
        if (a == None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            return;
        assert (a != None)
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (a is not None) 
        UNIQUE_IDENTIFIER = """*/"_""";
        a = a[::-1];
        if (a[-1][0].down()[0] != None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            t = a[-1][0].down()[list_index(a[-1][0].data(), v) + 1];
            UNIQUE_IDENTIFIER = """_"/*""";
            assert (t is not None); 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (t != None);
            while (t.down()[0] != None)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                t = t.down()[0];
                UNIQUE_IDENTIFIER = """_"/*""";
                assert (t is not None); 
                UNIQUE_IDENTIFIER = """*/"_""";
                assert (t != None);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            kw = t.data()[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);
            UNIQUE_IDENTIFIER = """_"/*""";
            assert (a is not None); 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (a != None);
            del t;
            t_ = list_index(a[0][0].data(), v);
            r = node_chval(r, a, t_, kw, len(a) - 1);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        elif (True)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            r = node_erase(r, v, self.max_len);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (list_size(r.data()) == 0)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            r = r.down()[0];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        self.root = r;

    def __repr__(self) -> str:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        r = self.root;
        return repr(r);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def to_list(self) -> list[T]:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        r = self.root;
        if (r == None)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            return [];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (r is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (r != None);
        return node_to_list(r, []);

    def __del__(self) -> None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        pass;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None):
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        if (not isinstance(k, item))// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (not isinstance(k, item));
            self.k : K = k;
            self.v : V|None = v;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        elif (True)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (isinstance(k, item));
            self.k, self.v = k.k, k.v;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";

    def __lt__(self, o: item[K, V]) -> bool:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return self.k < o.k;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __eq__(self, o: object|item[K, V]) -> bool:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        if (isinstance(o, item))// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            assert (isinstance(o, item));
            return self.k == o.k;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        return False;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __repr__(self) -> str:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return 'item' + repr((self.k, self.v));
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def to_list(self) -> list[K|V|None]:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return [self.k, self.v];
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        self.b_set: b_set[item[K, V]] = b_set();
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __getitem__(self, k:K)->V:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        r = self.b_set.find(item(k));
        if (not r)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            raise KeyError(k);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        tmp = r[0].v;
        UNIQUE_IDENTIFIER = """_"/*""";
        assert (tmp is not None); 
        UNIQUE_IDENTIFIER = """*/"_""";
        assert (tmp != None);
        return tmp;
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __setitem__(self, k:K, v:V)->None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        self.b_set.add(item(k, v));
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __delitem__(self, k:K)->None:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        self.b_set.remove(item(k));
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __repr__(self)->str:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return repr(self.b_set);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def __contains__(self, k:K) -> bool:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        return bool(self.b_set.find(item(k)));
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    def to_dict(self) -> dict[K, V]:
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
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
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";


if (__name__ == '__main__')// simple():
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    { // BEGIN
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

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
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 1)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert ((r in a_s) == (r in a_s));
            assert (r not in a_s or s_s.find(r)[0] == r);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 2 and a_s)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        f = set(s_s.to_list());
        assert (a_s == f);
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";

    print([time.time()-t,(t:=time.time())][0]);


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 1)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 2 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 3 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        if (q == 4 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                k = random.randint(-9999, 9999);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            try:
                del a_d[k];
                assert (0);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            except KeyError:
                pass;
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            del s_d[k];
        if (q == 5 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                k = random.randint(-9999, 9999);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
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
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        { // BEGIN
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
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
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
        if (q == 2 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)// simple():
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
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
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
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
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            if (a)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
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
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            if (a)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            { // BEGIN
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            if (a)// simple():
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                { // BEGIN
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
                del a[k];
                del s[k];
                assert (k not in a);
                assert (k not in s);
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
                } // END
                UNIQUE_IDENTIFIER = """_"/*""";
                ''' 
                UNIQUE_IDENTIFIER = """*/"_""";
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
            } // END
            UNIQUE_IDENTIFIER = """_"/*""";
            ''' 
            UNIQUE_IDENTIFIER = """*/"_""";
        random.choice(funcs)();
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
        } // END
        UNIQUE_IDENTIFIER = """_"/*""";
        ''' 
        UNIQUE_IDENTIFIER = """*/"_""";
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";
    } // END
    UNIQUE_IDENTIFIER = """_"/*""";
    ''' 
    UNIQUE_IDENTIFIER = """*/"_""";

