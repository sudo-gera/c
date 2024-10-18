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

x__max = max
x__min = min

int64_t = 1;
def REMOVE_CPP_BEGIN(a: typing.Any) -> None: pass


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
def list_slice_assign_zero(self: List_[T_], begin: int, end: int) -> None:
    return list_slice_assign(self, begin, end, [])
def list_slice_assign_one(self: List_[T_], begin: int, end: int, el: T_) -> None:
    return list_slice_assign(self, begin, end, [el])
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
# define elif else if
# define REMOVE_CPP_BEGIN(...)
# define REMOVE_CPP_END

UNIQUE_IDENTIFIER = """_"/*""";
''':'
UNIQUE_IDENTIFIER = """*/"_""";

#include <vector>
#include <memory>
#include <cinttypes>
#include <cstdint>
#include <cassert>

int64_t x__div(int64_t l, int64_t r){
    assert(r);
    return l / r;
}

int64_t x__max(int64_t a, int64_t b){
    return a>b?a:b;
}

int64_t x__min(int64_t a, int64_t b){
    return a<b?a:b;
}

template<typename T>
struct node_s{
    std::vector<T> data;
    std::vector<std::shared_ptr<node_s>> down;
};

template<typename T>
struct node{
    std::shared_ptr<node_s<T>> data_;
    std::vector<T>& data(){
        return data_->data;
    }
    std::vector<std::shared_ptr<node_s<T>>>& down(){
        return data_->down;
    }
};

template<typename T>
node<T> node_copy(node<T> self){
    return node{make_shared<node_s<T>>(*self.data_)};
}

UNIQUE_IDENTIFIER = """_"/*""";
':'''
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
    ''':'
UNIQUE_IDENTIFIER = """*/"_""";
template<typename T>
auto node_insert(node<T> self, T&& elem, int64_t max_len) -> node<T>{
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    assert (self is not None);
    ((""":" )) REMOVE_CPP_END ":""" ))
    assert (self != None);
    self = node_copy(self);
    if (list_contains(self.data(), elem))// simple():
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t // int64_t
        t = list_index(self.data(), elem);
        self.data()[t] = elem;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
    elif (self.down()[0] == None)// simple():
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            w += 1;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        list_insert(self.data(), w, elem);
        list_insert(self.down(), 0, None);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
    elif (True)// simple():
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            w += 1;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        self.down()[w] = node_insert(self.down()[w], elem, max_len);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        node
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        tmp = self.down()[w];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (tmp != None);
        if (list_size(tmp.data()) > max_len)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (list_size(tmp.data()) == 1 + max_len);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            node
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            q = node_copy(tmp);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            node
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            a = node_copy(q);
            list_slice_assign_zero(a.data(),x__div( max_len ,  2),list_size(a.data()));
            list_slice_assign_zero(a.down(),x__div( max_len ,  2) + 1,list_size(a.down()));
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            auto
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            kw = q.data()[x__div(max_len ,  2)];
            list_slice_assign_zero(q.data(), 0,x__div( max_len ,  2) + 1);
            list_slice_assign_zero(q.down(), 0,x__div(max_len ,  2) + 1);
            list_insert(self.data(), w, kw);
            self.down()[w] = q;
            list_insert(self.down(), w, a);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
    return self;
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))
template<typename T>
auto node_find_path(node<T> self, const T& elem) -> std::vector<std::pair<node<T>, int64_t>>{
REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
def node_find_path(self: node[T], elem: T) -> list[tuple[node[T], int]]:
    ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    std::vector<std::pair<node<T>, int64_t>> output;
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    output : list[tuple[node[T], int]] = [];
    ((""":" )) REMOVE_CPP_END ":""" ))

    if (node_find_path_(self, elem, output))// simple():
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return output;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    return std::vector<std::pair<node<T>, int64_t>>();
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    return [];
    ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))
template<typename T, typename OUT_IT>
auto node_find_path_(node<T> self , const T& elem, OUT_IT output) -> bool{
REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
def node_find_path_(self: node[T], elem: T, output: list[tuple[node[T], int]]) -> bool:
    ((""":" )) REMOVE_CPP_END ":""" ))

    if (list_contains(self.data(), elem))// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        output.append((self, list_index(self.data(), (elem))));
        return True;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    if (self.down()[0] == None)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        return False;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    int64_t
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

    w = 0;
    while (w < list_size(self.data()) and self.data()[w] < elem)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        w += 1;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    node
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

    tmp = self.down()[w];
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    assert (tmp is not None);
    ((""":" )) REMOVE_CPP_END ":""" ))
    assert (tmp != None);
    if (node_find_path_(tmp, elem, output))// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        output.append((self, w));
        return True;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    return False;

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))
template<typename T>
auto node_erase(node<T> self  , const T& elem, int64_t max_len) -> node<T>{
REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
def node_erase(self: node[T], elem: T, max_len: int) -> node[T]:
    ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    node<T> t;
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    t: None|node[T];
    ((""":" )) REMOVE_CPP_END ":""" ))

    self = node_copy(self);
    if (self.down()[0] == None)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        t_ = list_index(self.data(), (elem));
        list_erase(self.data(), t_);
        list_erase(self.down(), 0);

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    elif (True)// simple():
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            w += 1;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        node
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        tmp = self.down()[w];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (tmp != None);
        self.down()[w] = node_erase(tmp, elem, max_len);
        tmp = self.down()[w];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (tmp != None);
        if (list_size(tmp.data()) <x__div( max_len ,  2))// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (list_size(tmp.data()) ==x__div( max_len ,  2) - 1);

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            int64_t
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            e = 0;
            if (w)// simple():

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                e = w - 1;

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

            elif (True)// simple():

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                e = w + 1;

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            int64_t
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            q = x__max(w, e);

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            int64_t
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            r = x__min(w, e);

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            node
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            tmp = self.down()[e];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            assert (tmp is not None);
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (tmp != None);
            if (list_size(tmp.data()) ==x__div( max_len ,  2))// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                tmp = self.down()[q];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);
                tmp = self.down()[r];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                auto&
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                __t = tmp.data();
                list_append(__t, self.data()[r]);
                list_slice_assign(t.data(), 0, 0, __t);
                tmp = self.down()[r];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                list_slice_assign(t.down(), 0,0,tmp.down());
                list_slice_assign_one(self.down(), r,q + 1, t);
                list_slice_assign_zero(self.data(), r,q );
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            elif (True)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                tmp = self.down()[w];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                int64_t
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                l = (q - w) * list_size(t.down());


                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                int64_t
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                tmp_1 = l;
                if (tmp_1 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_1 += list_size(t.data());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                if (tmp_1 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_1 = 0;

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                if (tmp_1 > list_size(t.data()))// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_1 = list_size(t.data());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                list_slice_assign_one(t.data(), tmp_1, tmp_1, self.data()[r]);
                tmp = self.down()[e];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                tmp_1 = l;
                list_slice_assign_one(t.down(), tmp_1, tmp_1, tmp.down()[(e - q + list_size(tmp.down())) % list_size(tmp.down())]);
                self.down()[w] = t;
                tmp = self.down()[e];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                self.data()[r] = tmp.data()[(e - q + list_size(tmp.data())) % list_size(tmp.data())];
                tmp = self.down()[e];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);
                tmp_1 = e - q;
                if (tmp_1 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_1 += list_size(t.data());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                int64_t
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

                tmp_2 = list_size(t.data()) * (q - e) + (q - w);
                if (tmp_2 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_2 += list_size(t.data());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                list_slice_assign_zero(t.data(), tmp_1, tmp_2);
                tmp_1 = e - q;
                if (tmp_1 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_1 += list_size(t.down());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                tmp_2 = list_size(t.down()) * (q - e) + (q - w);
                if (tmp_2 < 0)// simple():

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    { // BEGIN
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                    tmp_2 += list_size(t.data());

                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    ''':' /* REMOVE_PYTHON_BEGIN */
                    ((""":" )) REMOVE_CPP_END ":""" ))
                    } // END
                    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                    /* REMOVE_PYTHON_END */ ':'''
                    ((""":" )) REMOVE_CPP_END ":""" ))

                list_slice_assign_zero(t.down(), tmp_1, tmp_2);
                self.down()[e] = t;

                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    return self;

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))
template<typename T>
auto node_to_list(node<T> self, std::vector<T>& l) -> std::vector<T>&{
REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
def node_to_list(self: node[T], l: list[T]) -> list[T]:
    ((""":" )) REMOVE_CPP_END ":""" ))

    if (self.down()[0] == None)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        i_ = 0;
        while (i_ < list_size(self.data()))// simple():

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            auto
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            w_ = self.data()[i_];
            l.append(w_);
            i_ += 1;

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    elif (True)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        node
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        tmp = self.down()[0];
        assert (tmp != None);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        node_to_list(tmp, l);

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        i_ = 0;
        while (i_ < list_size(self.data()))// simple():

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            int64_t
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            w = i_;
            l.append(self.data()[w]);
            tmp = self.down()[w + 1];

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            assert (isinstance(tmp, node));
            ((""":" )) REMOVE_CPP_END ":""" ))

            node_to_list(tmp, l);
            i_ += 1;

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    return l;

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))
template<typename T>
auto node_chval(node<T> self, const std::vector<std::pair<node<T>, int64_t>>& a,int64_t t,T kw,int64_t n) -> node<T>{
REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
def node_chval(self: node[T], a: list[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
    ((""":" )) REMOVE_CPP_END ":""" ))

    self = node_copy(self);
    if (n)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        int64_t
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        v = a[n][1];

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        node
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        tmp = self.down()[v];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (tmp != None);
        self.down()[v] = node_chval(tmp, a, t, kw, n - 1);

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    elif (True)// simple():

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

        assert (self.data() != None);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (isinstance(t, int));
        ((""":" )) REMOVE_CPP_END ":""" ))
        self.data()[t] = kw;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    return self;

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))


REMOVE_CPP_BEGIN(( int64_t // int64_t ))
Node = node[T] | None;
((""":" )) REMOVE_CPP_END ":""" ))

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
''':' /* REMOVE_PYTHON_BEGIN */
((""":" )) REMOVE_CPP_END ":""" ))

template<typename T>
struct b_set{
    node root;
    int64_t max_len = 99;
};

REMOVE_CPP_BEGIN(( int64_t // int64_t ))
/* REMOVE_PYTHON_END */ ':'''
class b_set(typing.Generic[T]):

    def __init__(self) -> None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        self.root: Node[T] = None;
        self.max_len = 99;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    ((""":" )) REMOVE_CPP_END ":""" ))

    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    template<typename T>
    auto add(T&& v) -> void{
        auto& self = *this;
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    def add(self, v: T) -> None:
        ((""":" )) REMOVE_CPP_END ":""" ))

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        auto q = node{std::vector<T>(), std::vector<node<T>>({self.root})};
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        q = node(data=List_([]), down=List_([self.root, ]));
        ((""":" )) REMOVE_CPP_END ":""" ))

        q = node_insert(q, v, self.max_len);
        if (not list_size(q.data()))// simple():

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

            tmp = q.down()[0];

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            assert (tmp is not None);
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (tmp != None);

            q = tmp;

            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

        self.root = q;

        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))




    def find(self, v: T) -> list[T]:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        r = self.root;
        if (r == None)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            return [];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        assert (r != None)
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (r is not None)
        ((""":" )) REMOVE_CPP_END ":""" ))
        f = node_find_path(r, v);
        if (not f)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            return [];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        assert (f != None)
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (f is not None)
        ((""":" )) REMOVE_CPP_END ":""" ))
        _f = f[0];
        return [_f[0].data()[_f[1]]];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __contains__(self, v: T) -> bool:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return bool(self.find(v));
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def remove(self, v: T) -> None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        r = self.root;
        if (r == None)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            return;
        assert (r != None)
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (r is not None)
        ((""":" )) REMOVE_CPP_END ":""" ))
        a = node_find_path(r, v);
        if (not a)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            return;
        assert (a)
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (a is not None)
        ((""":" )) REMOVE_CPP_END ":""" ))
        a = a[::-1];
        if (a[-1][0].down()[0] != None)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            t = a[-1][0].down()[list_index(a[-1][0].data(), v) + 1];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            assert (t is not None);
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (t != None);
            while (t.down()[0] != None)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                t = t.down()[0];
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                assert (t is not None);
                ((""":" )) REMOVE_CPP_END ":""" ))
                assert (t != None);
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            kw = t.data()[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            assert (a);
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (a);
            del t;
            t_ = list_index(a[0][0].data(), v);
            r = node_chval(r, a, t_, kw, len(a) - 1);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        elif (True)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            r = node_erase(r, v, self.max_len);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (list_size(r.data()) == 0)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            r = r.down()[0];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        self.root = r;

    def __repr__(self) -> str:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        r = self.root;
        return repr(r);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def to_list(self) -> list[T]:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        r = self.root;
        if (r == None)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            return [];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (r is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (r != None);
        return node_to_list(r, []);

    def __del__(self) -> None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        pass;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))


K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');


@functools.total_ordering
class item(typing.Generic[K, V]):

    def __init__(self, k: K | item[K,V], v: V|None=None):
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        if (not isinstance(k, item))// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (not isinstance(k, item));
            self.k : K = k;
            self.v : V|None = v;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        elif (True)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (isinstance(k, item));
            self.k, self.v = k.k, k.v;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))

    def __lt__(self, o: item[K, V]) -> bool:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return self.k < o.k;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __eq__(self, o: object|item[K, V]) -> bool:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        if (isinstance(o, item))// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            assert (isinstance(o, item));
            return self.k == o.k;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        return False;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __repr__(self) -> str:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return 'item' + repr((self.k, self.v));
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def to_list(self) -> list[K|V|None]:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return [self.k, self.v];
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))


class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        self.b_set: b_set[item[K, V]] = b_set();
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __getitem__(self, k:K)->V:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        r = self.b_set.find(item(k));
        if (not r)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            raise KeyError(k);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        tmp = r[0].v;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) REMOVE_CPP_END ":""" ))
        assert (tmp != None);
        return tmp;
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __setitem__(self, k:K, v:V)->None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        self.b_set.add(item(k, v));
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __delitem__(self, k:K)->None:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        self.b_set.remove(item(k));
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __repr__(self)->str:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return repr(self.b_set);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def __contains__(self, k:K) -> bool:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        return bool(self.b_set.find(item(k)));
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    def to_dict(self) -> dict[K, V]:
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
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
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))


if (__name__ == '__main__')// simple():
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    { // BEGIN
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

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
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 1)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert ((r in a_s) == (r in a_s));
            assert (r not in a_s or s_s.find(r)[0] == r);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 2 and a_s)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        f = set(s_s.to_list());
        assert (a_s == f);
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))

    print([time.time()-t,(t:=time.time())][0]);


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 1)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 2 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 3 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        if (q == 4 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                k = random.randint(-9999, 9999);
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            try:
                del a_d[k];
                assert (0);
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            except KeyError:
                pass;
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            del s_d[k];
        if (q == 5 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                k = random.randint(-9999, 9999);
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
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
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        { // BEGIN
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
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
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
        if (q == 2 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)// simple():
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
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
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
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
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            if (a)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
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
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            if (a)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            { // BEGIN
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
            if (a)// simple():
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                { // BEGIN
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
                del a[k];
                del s[k];
                assert (k not in a);
                assert (k not in s);
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                ''':' /* REMOVE_PYTHON_BEGIN */
                ((""":" )) REMOVE_CPP_END ":""" ))
                } // END
                REMOVE_CPP_BEGIN(( int64_t // int64_t ))
                /* REMOVE_PYTHON_END */ ':'''
                ((""":" )) REMOVE_CPP_END ":""" ))
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            ''':' /* REMOVE_PYTHON_BEGIN */
            ((""":" )) REMOVE_CPP_END ":""" ))
            } // END
            REMOVE_CPP_BEGIN(( int64_t // int64_t ))
            /* REMOVE_PYTHON_END */ ':'''
            ((""":" )) REMOVE_CPP_END ":""" ))
        random.choice(funcs)();
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        ''':' /* REMOVE_PYTHON_BEGIN */
        ((""":" )) REMOVE_CPP_END ":""" ))
        } // END
        REMOVE_CPP_BEGIN(( int64_t // int64_t ))
        /* REMOVE_PYTHON_END */ ':'''
        ((""":" )) REMOVE_CPP_END ":""" ))
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    ''':' /* REMOVE_PYTHON_BEGIN */
    ((""":" )) REMOVE_CPP_END ":""" ))
    } // END
    REMOVE_CPP_BEGIN(( int64_t // int64_t ))
    /* REMOVE_PYTHON_END */ ':'''
    ((""":" )) REMOVE_CPP_END ":""" ))

