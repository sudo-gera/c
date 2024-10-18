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
def PAUSE_CPP(a: typing.Any) -> None: pass


class ComparableProto(typing.Protocol):
    def __lt__(self: T, __other: T) -> bool: ...;

T_ = typing.TypeVar('T_');

def move(q: T_) -> T_:
    return q

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
    def __bool__(self) -> bool:
        assert False
        return False
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
def list_reverse(self: List_[T_]) -> None:
    self.l = self.l[::-1]
T0 = typing.TypeVar('T0');
T1 = typing.TypeVar('T1');
def tuple_get_0(a: tuple[T0, T1]) -> T0:
    return a[0]
def tuple_get_1(a: tuple[T0, T1]) -> T1:
    return a[1]

T = typing.TypeVar('T', bound=ComparableProto);
T = typing.TypeVar('T') ; # type: ignore

###################################################################################################################################

UNIQUE_IDENTIFIER = """*/"_""";

UNIQUE_IDENTIFIER = """_"/*""";
''':'
UNIQUE_IDENTIFIER = """*/"_""";

#include <vector>
#include <memory>
#include <cinttypes>
#include <cstdint>
#include <cassert>
#include <optional>
#include <iostream>
#include <set>
#include <random>

# define True true
# define False false
# define None nullptr
# define elif else if
# define PAUSE_CPP(...)
# define RESUME_CPP
# define PAUSE_PYTHON
# define RESUME_PYTHON
# define move std::move
# define forward std::forward

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
int64_t list_size(const std::vector<T>& a){
    return a.size();
}

template<typename T>
int64_t len(const std::vector<T>& a){
    return a.size();
}

template<typename T>
bool list_contains(const std::vector<T>& a, const T& e){
    return std::find(a.begin(), a.end(), e) != a.end();
}

template<typename T>
int64_t list_index(const std::vector<T>& a, const T& e){
    return std::find(a.begin(), a.end(), e) - a.begin();
}

template<typename T>
void list_insert(std::vector<T>& a, int64_t pos, const T& e){
    a.insert(a.begin() + pos, e);
}

template<typename T>
void list_append(std::vector<T>& a, const T& e){
    a.push_back(e);
}

template<typename T>
void list_erase(std::vector<T>& a, int64_t e){
    std::vector<T> f;
    std::copy(a.begin(), a.begin()+e, std::back_inserter(f));
    std::copy(a.begin()+e+1, a.end(), std::back_inserter(f));
    swap(f, a);
}



auto print_one(auto&&a){
    std::cout << a << " ";
    return 0;
}

void print(auto&&...a){
    (print_one(a),...);
    std::cout << std::endl;
}

# define make_int_const(x) (std::integral_constant<int64_t, x>())

auto tuple_get_0(auto&&a){
    return a.first;
}

auto tuple_get_1(auto&&a){
    return a.second;
}

template<typename T>
void list_slice_assign(std::vector<T>& a, int64_t begin, int64_t end, std::vector<T> v){
    std::vector<T> f;
    std::copy(a.begin(), a.begin() + begin, std::back_inserter(f));
    std::copy(v.begin(), v.end(), std::back_inserter(f));
    std::copy(a.begin() + end, a.end() , std::back_inserter(f));
    swap(a, f);
}

template<typename T>
void list_slice_assign_zero(std::vector<T>& a, int64_t begin, int64_t end){
    list_slice_assign(a, begin, end, std::vector<T>());
}

template<typename T>
void list_slice_assign_one(std::vector<T>& a, int64_t begin, int64_t end, T val){
    list_slice_assign(a, begin, end, std::vector<T>({move(val)}));
}

template<typename T>
void list_reverse(std::vector<T>& a){
    std::reverse(a.begin(), a.end());
}


template<typename T>
struct node;

template<typename T>
struct node_s{
    std::vector<T> data;
    std::vector<node<T>> down = std::vector<node<T>>(1);
};

template<typename T>
struct node{
    std::shared_ptr<node_s<T>> data_;
    std::vector<T>& data(){
        return data_->data;
    }
    std::vector<node<T>>& down(){
        return data_->down;
    }
    operator std::shared_ptr<T>()const{
        return data_;
    }
    operator bool()const{
        return data_ != nullptr;
    }
    bool operator!=(std::nullptr_t){
        return data_ != nullptr;
    }
    bool operator==(std::nullptr_t){
        return data_ == nullptr;
    }
    node(std::shared_ptr<node_s<T>> a): data_(a){}
    node(nullptr_t){}
    node(){}
};

template<typename T>
node<T> create_node(){
    return node<T>(std::make_shared<node_s<T>>());
}


template<typename T>
node<T> node_copy(node<T> self){
    if (self){
        return node<T>{std::make_shared<node_s<T>>(*self.data_)};
    }else{
        return node<T>{std::shared_ptr<node_s<T>>()};
    }
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
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    assert (self is not None);
    ((""":" )) RESUME_CPP ":""" ))
    assert (self != None);
    self = node_copy(self);
    if (list_contains(self.data(), elem))// simple():
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        ':'''
        ((""":" )) RESUME_CPP ":""" ))
        int64_t // int64_t
        t = list_index(self.data(), elem);
        self.data()[t] = elem;
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
    elif (self.down()[0] == None)// simple():
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            w += 1;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        list_insert(self.data(), w, elem);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node<T> tmp_3 = {nullptr};
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        tmp_3 = None;
        list_insert(self.down(), 0, tmp_3);
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
    elif (True)// simple():
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            w += 1;
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        self.down()[w] = node_insert(self.down()[w], move(elem), max_len);
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        tmp = self.down()[w];
        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (tmp != None);
        if (list_size(tmp.data()) > max_len)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            assert (list_size(tmp.data()) == 1 + max_len);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            node
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            q = node_copy(tmp);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            node
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            a = node_copy(q);
            list_slice_assign_zero(a.data(),x__div( max_len ,  2),list_size(a.data()));
            list_slice_assign_zero(a.down(),x__div( max_len ,  2) + 1,list_size(a.down()));
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            auto
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            kw = q.data()[x__div(max_len ,  2)];
            list_slice_assign_zero(q.data(), 0,x__div( max_len ,  2) + 1);
            list_slice_assign_zero(q.down(), 0,x__div(max_len ,  2) + 1);
            list_insert(self.data(), w, kw);
            self.down()[w] = q;
            list_insert(self.down(), w, a);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
    return self;
    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
template<typename T>
auto node_find_path(node<T> self, const T& elem) -> std::vector<std::pair<node<T>, int64_t>>{
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
def node_find_path(self: node[T], elem: T) -> List_[tuple[node[T], int]]:
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    std::vector<std::pair<node<T>, int64_t>> output;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    output : List_[tuple[node[T], int]] = List_([]);
    ((""":" )) RESUME_CPP ":""" ))

    if (node_find_path_(self, elem, output))// simple():
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        return output;
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    return std::vector<std::pair<node<T>, int64_t>>();
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    return List_([]);
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
template<typename T, typename OUT_IT>
auto node_find_path_(node<T> self , const T& elem, OUT_IT& output) -> bool{
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
def node_find_path_(self: node[T], elem: T, output: List_[tuple[node[T], int]]) -> bool:
    ((""":" )) RESUME_CPP ":""" ))

    if (list_contains(self.data(), elem))// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))

        list_append(output, std::pair{self, list_index(self.data(), (elem))});

        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''

        list_append(output, (self, list_index(self.data(), (elem))));

        ((""":" )) RESUME_CPP ":""" ))

        return True;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    if (self.down()[0] == None)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        return False;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    int64_t
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

    w = 0;
    while (w < list_size(self.data()) and self.data()[w] < elem)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        w += 1;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    node
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

    tmp = self.down()[w];
    PAUSE_CPP(( int64_t // int64_t ))
    assert (tmp is not None);
    ((""":" )) RESUME_CPP ":""" ))
    assert (tmp != None);
    if (node_find_path_(tmp, elem, output))// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))

        list_append(output, std::pair{self, w});

        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        list_append(output, (self, w));
        ((""":" )) RESUME_CPP ":""" ))

        return True;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    return False;

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
template<typename T>
auto node_erase(node<T> self  , const T& elem, int64_t max_len) -> node<T>{
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
def node_erase(self: node[T], elem: T, max_len: int) -> node[T]:
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    node<T> t;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    t: None|node[T];
    ((""":" )) RESUME_CPP ":""" ))

    self = node_copy(self);
    if (self.down()[0] == None)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        t_ = list_index(self.data(), (elem));
        list_erase(self.data(), t_);
        list_erase(self.down(), 0);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    elif (True)// simple():
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        
        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            w += 1;
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        tmp = self.down()[w];
        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (tmp != None);
        self.down()[w] = node_erase(tmp, elem, max_len);
        tmp = self.down()[w];
        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (tmp != None);
        if (list_size(tmp.data()) <x__div( max_len ,  2))// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            assert (list_size(tmp.data()) ==x__div( max_len ,  2) - 1);

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            int64_t
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            e = 0;
            if (w)// simple():

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                e = w - 1;

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

            elif (True)// simple():

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                e = w + 1;

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            int64_t
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            q = x__max(w, e);

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            int64_t
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            r = x__min(w, e);

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            node
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            tmp = self.down()[e];
            PAUSE_CPP(( int64_t // int64_t ))
            assert (tmp is not None);
            ((""":" )) RESUME_CPP ":""" ))
            assert (tmp != None);
            if (list_size(tmp.data()) ==x__div( max_len ,  2))// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                tmp = self.down()[q];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);
                tmp = self.down()[r];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                auto&
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                __t = tmp.data();
                list_append(__t, self.data()[r]);
                list_slice_assign(t.data(), 0, 0, __t);
                tmp = self.down()[r];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                list_slice_assign(t.down(), 0,0,tmp.down());
                list_slice_assign_one(self.down(), r,q + 1, t);
                list_slice_assign_zero(self.data(), r,q );
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
            elif (True)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                tmp = self.down()[w];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                int64_t
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                l = (q - w) * list_size(t.down());


                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                int64_t
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                tmp_1 = l;
                if (tmp_1 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_1 += list_size(t.data());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                if (tmp_1 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_1 = 0;

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                if (tmp_1 > list_size(t.data()))// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_1 = list_size(t.data());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                list_slice_assign_one(t.data(), tmp_1, tmp_1, self.data()[r]);
                tmp = self.down()[e];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                tmp_1 = l;
                list_slice_assign_one(t.down(), tmp_1, tmp_1, tmp.down()[(e - q + list_size(tmp.down())) % list_size(tmp.down())]);
                self.down()[w] = t;
                tmp = self.down()[e];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                self.data()[r] = tmp.data()[(e - q + list_size(tmp.data())) % list_size(tmp.data())];
                tmp = self.down()[e];
                PAUSE_CPP(( int64_t // int64_t ))
                assert (tmp is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (tmp != None);
                t = node_copy(tmp);
                tmp_1 = e - q;
                if (tmp_1 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_1 += list_size(t.data());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                int64_t
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                tmp_2 = list_size(t.data()) * (q - e) + (q - w);
                if (tmp_2 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_2 += list_size(t.data());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                list_slice_assign_zero(t.data(), tmp_1, tmp_2);
                tmp_1 = e - q;
                if (tmp_1 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_1 += list_size(t.down());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                tmp_2 = list_size(t.down()) * (q - e) + (q - w);
                if (tmp_2 < 0)// simple():

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    { // BEGIN
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                    tmp_2 += list_size(t.data());

                    PAUSE_CPP(( int64_t // int64_t ))
                    ''':' PAUSE_PYTHON
                    ((""":" )) RESUME_CPP ":""" ))
                    } // END
                    PAUSE_CPP(( int64_t // int64_t ))
                    RESUME_PYTHON ':'''
                    ((""":" )) RESUME_CPP ":""" ))

                list_slice_assign_zero(t.down(), tmp_1, tmp_2);
                self.down()[e] = t;

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    return self;

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
template<typename T>
auto node_to_list(node<T> self, std::vector<T>& l) -> std::vector<T>&{
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
def node_to_list(self: node[T], l: list[T]) -> list[T]:
    ((""":" )) RESUME_CPP ":""" ))

    if (self.down()[0] == None)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        i_ = 0;
        while (i_ < list_size(self.data()))// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            auto
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            w_ = self.data()[i_];
            l.append(w_);
            i_ += 1;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    elif (True)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        tmp = self.down()[0];
        assert (tmp != None);
        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        node_to_list(tmp, l);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        i_ = 0;
        while (i_ < list_size(self.data()))// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            int64_t
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            w = i_;
            l.append(self.data()[w]);
            tmp = self.down()[w + 1];

            PAUSE_CPP(( int64_t // int64_t ))
            assert (isinstance(tmp, node));
            ((""":" )) RESUME_CPP ":""" ))

            node_to_list(tmp, l);
            i_ += 1;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    return l;

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
template<typename T>
auto node_chval(node<T> self, const std::vector<std::pair<node<T>, int64_t>>& a,int64_t t,T kw,int64_t n) -> node<T>{
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
def node_chval(self: node[T], a: List_[tuple[node[T], int]], t: int, kw: T, n: int) -> node[T]:
    ((""":" )) RESUME_CPP ":""" ))

    self = node_copy(self);
    if (n)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        int64_t
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        v = tuple_get_1(a[n]);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        tmp = self.down()[v];
        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (tmp != None);
        self.down()[v] = node_chval(tmp, a, t, kw, n - 1);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    elif (True)// simple():

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        assert (self.data() != None);
        assert (isinstance(t, int));
        ((""":" )) RESUME_CPP ":""" ))
        self.data()[t] = kw;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    return self;

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))


PAUSE_CPP(( int64_t // int64_t ))
Node = node[T] | None;
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))

template<typename T>
struct b_set{
    node<T> root;
    int64_t max_len = 5;

PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
class b_set(typing.Generic[T]):

    def __init__(self) -> None:
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        self.root: Node[T] = None;
        self.max_len = 99;
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto add(T&& v) -> void{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def add(self, v: T) -> None:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node<T> q = create_node<T>();
        q.down()[0] = self.root;
        // auto q = std::make_shared<node_s<T>>(node_s<T>{std::vector<T>(), std::vector<node<T>>({self.root})});
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        q = node(data=List_([]), down=List_([self.root, ]));
        ((""":" )) RESUME_CPP ":""" ))

        q = node_insert(q, move(v), self.max_len);
        if (not list_size(q.data()))// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            node<T>
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            tmp = q.down()[0];

            PAUSE_CPP(( int64_t // int64_t ))
            assert (tmp is not None);
            ((""":" )) RESUME_CPP ":""" ))
            assert (tmp);

            q = tmp;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        self.root = q;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto find(const T& v) -> std::vector<T>{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def find(self, v: T) -> list[T]:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        r = self.root;
        if (r == None)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            return std::vector<T>();
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            return [];
            ((""":" )) RESUME_CPP ":""" ))

        assert (r != None);
        PAUSE_CPP(( int64_t // int64_t ))
        assert (r is not None);
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        auto
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        f = node_find_path(r, v);
        if (not list_size(f))// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            return std::vector<T>();

            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''

            return [];

            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        assert (f != None);
        assert (f is not None)
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        auto&
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        _f = f[0];

        PAUSE_CPP(( int64_t // int64_t ))
        return [tuple_get_0(_f).data()[tuple_get_1(_f)]]
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        return std::vector<T>({tuple_get_0(_f).data()[tuple_get_1(_f)]});
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto contains(const T& v) -> bool{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __contains__(self, v: T) -> bool:
        ((""":" )) RESUME_CPP ":""" ))

        return bool(len(self.find(v)));

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto remove(const T& v) -> void{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def remove(self, v: T) -> None:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        r = self.root;
        if (r == None)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            return;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        assert (r != None);
        PAUSE_CPP(( int64_t // int64_t ))
        assert (r is not None)
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        auto
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        a = node_find_path(r, v);
        if (not list_size(a))// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            return;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        assert (list_size(a));
        PAUSE_CPP(( int64_t // int64_t ))
        assert (a is not None)
        ((""":" )) RESUME_CPP ":""" ))

        list_reverse(a);
        if (tuple_get_0(a[list_size(a)-1]).down()[0] != None)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            node
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            t = tuple_get_0(a[list_size(a)-1]).down()[list_index(tuple_get_0(a[list_size(a)-1]).data(), v) + 1];

            PAUSE_CPP(( int64_t // int64_t ))
            assert (t is not None);
            ((""":" )) RESUME_CPP ":""" ))
            assert (t != None);

            while (t.down()[0] != None)// simple():

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

                t = t.down()[0];

                PAUSE_CPP(( int64_t // int64_t ))
                assert (t is not None);
                ((""":" )) RESUME_CPP ":""" ))
                assert (t != None);

                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            auto
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            kw = t.data()[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);

            PAUSE_CPP(( int64_t // int64_t ))
            assert (list_size(a));
            ((""":" )) RESUME_CPP ":""" ))
            assert (list_size(a));

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            int64_t
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            t_ = list_index(tuple_get_0(a[0]).data(), v);
            r = node_chval(r, a, t_, kw, list_size(a) - 1);

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        elif (True)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            r = node_erase(r, v, self.max_len);

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        if (list_size(r.data()) == 0)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            r = r.down()[0];

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        self.root = r;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))


    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto to_list() -> std::vector<T>{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def to_list(self) -> list[T]:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        node
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        r = self.root;
        if (r == None)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            return [];
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            return std::vector<T>();
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        PAUSE_CPP(( int64_t // int64_t ))
        assert (r is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (r != None);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        return node_to_list(r, std::vector<T>());
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        return node_to_list(r, []);
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    return std::vector<T>();
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
}; // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))


PAUSE_CPP(( int64_t // int64_t ))
K = typing.TypeVar('K', bound=ComparableProto);
K = typing.TypeVar('K') ; # type: ignore
V = typing.TypeVar('V');
((""":" )) RESUME_CPP ":""" ))


PAUSE_CPP(( int64_t // int64_t ))
@functools.total_ordering
class item(typing.Generic[K, V]):
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    template<typename K, typename V>
    struct item{
        K k;
        std::optional<V> v;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))


    PAUSE_CPP(( int64_t // int64_t ))
    def __init__(self, k: K | item[K,V], v: V|None=None):
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        if (not isinstance(k, item))// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            assert (not isinstance(k, item));
            self.k : K = k;
            self.v : V|None = v;
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        elif (True)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            assert (isinstance(k, item));
            self.k, self.v = k.k, k.v;
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto operator<(const item<K, V>& o) -> bool{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __lt__(self, o: item[K, V]) -> bool:
        ((""":" )) RESUME_CPP ":""" ))

        return self.k < o.k;

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto operator==(const item<K, V>& o) -> bool{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __eq__(self, o: object|item[K, V]) -> bool:
        if (isinstance(o, item))// simple():
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

            PAUSE_CPP(( int64_t // int64_t ))
            assert (isinstance(o, item));
            ((""":" )) RESUME_CPP ":""" ))
            return self.k == o.k;

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        return False;
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))


    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto to_list() -> std::pair<K, std::optional<V>>{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def to_list(self) -> list[K|V|None]:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        return {k, v};
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        return [self.k, self.v];
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))


    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    }; // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))


PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))

template<typename K, typename V>
struct b_dict{
    b_set<item<K, V>> b_set_;

PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
class b_dict(typing.Generic[K, V]):

    def __init__(self) -> None:
        self.b_set: b_set[item[K, V]] = b_set();

    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto operator[](const K& k) -> V{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __getitem__(self, k:K)->V:
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        auto
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        r = self.b_set.find(item(k));
        if (not r)// simple():

            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            return std::optional<V>();
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            raise KeyError(k);
            ((""":" )) RESUME_CPP ":""" ))


            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        auto
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

        tmp = r[0].v;

        PAUSE_CPP(( int64_t // int64_t ))
        assert (tmp is not None);
        ((""":" )) RESUME_CPP ":""" ))
        assert (tmp != None);

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        return {tmp};
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        return tmp;
        ((""":" )) RESUME_CPP ":""" ))

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto setitem(const K& k, V&&v) -> void{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __setitem__(self, k:K, v:V)->None:
        ((""":" )) RESUME_CPP ":""" ))

        self.b_set.add(item(k, v));

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto delitem(const K& k) -> void{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __delitem__(self, k:K)->None:
        ((""":" )) RESUME_CPP ":""" ))

        self.b_set.remove(item(k));

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    auto contains(const K& k) -> bool{
        auto& self = *this;
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    def __contains__(self, k:K) -> bool:
        ((""":" )) RESUME_CPP ":""" ))

        return bool(self.b_set.find(item(k)));

        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    def to_dict(self) -> dict[K, V]:
        r_:list[item[K, V]] = self.b_set.to_list();
        r:List_[item[K, V]] = List_([])
        i_ = 0
        while i_ < len(r_):
            w = r_[i_]
            e = w.to_list()
            list_append(r, e) # type: ignore
            i_ += 1
        return dict(r); # type: ignore
    ((""":" )) RESUME_CPP ":""" ))

    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    }; // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

UNIQUE_IDENTIFIER = """_"/*""";

PAUSE_CPP(( int64_t // int64_t ))
if (__name__ == '__main__')// simple():
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    int main()
    { // BEGIN
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

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
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            r = random.randint(-9999, 9999);
            a_s.add(r);
            s_s.add(r);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 1)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            r = random.choice(list(a_s)) if a_s and random.randint(
                0, -1 + 2) else random.randint(0, -1 + 9);
            assert ((r in a_s) == (r in a_s));
            assert (r not in a_s or s_s.find(r)[0] == r);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 2 and a_s)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            r = random.choice(list(a_s));
            a_s.remove(r);
            s_s.remove(r);
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        f = set(s_s.to_list());
        assert (a_s == f);
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))


    a_d: dict[int, int] = dict();
    s_d: b_dict[int, int] = b_dict();
    for w in range(49):
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
        if (q == 0)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 1)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 2 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 3 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d));
            del a_d[k];
            del s_d[k];
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        if (q == 4 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                k = random.randint(-9999, 9999);
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
            try:
                del a_d[k];
                assert (0);
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
            except KeyError:
                pass;
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
            del s_d[k];
        if (q == 5 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.randint(-9999, 9999);
            while (k in a_d)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                k = random.randint(-9999, 9999);
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
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
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        { // BEGIN
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
        k = random.choice(list(a_d));
        del a_d[k];
        del s_d[k];
        w += 1;
        if (w % 100 == 0)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
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
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            v = random.randint(-9999, 9999);
            a_d[k] = v;
            s_d[k] = v;
        if (q == 1)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d)) if a_d and random.randint(
                0, 1) else random.randint(-9999, 9999);
            assert ((k in a_d) == (k in s_d));
        if (q == 2 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            k = random.choice(list(a_d));
            a_d[k] == s_d[k];
        if (q == 3 and a_d)// simple():
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
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
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
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
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            if (a)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
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
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            if (a)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
        @(lambda x: funcs.setdefault(len(funcs), x))
        def rem() -> None:
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            { // BEGIN
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
            if (a)// simple():
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                { // BEGIN
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
                k = random.choice([*a.keys()]);
                assert (k in a);
                assert (k in s);
                assert (a[k] == s[k]);
                del a[k];
                del s[k];
                assert (k not in a);
                assert (k not in s);
                PAUSE_CPP(( int64_t // int64_t ))
                ''':' PAUSE_PYTHON
                ((""":" )) RESUME_CPP ":""" ))
                } // END
                PAUSE_CPP(( int64_t // int64_t ))
                RESUME_PYTHON ':'''
                ((""":" )) RESUME_CPP ":""" ))
            PAUSE_CPP(( int64_t // int64_t ))
            ''':' PAUSE_PYTHON
            ((""":" )) RESUME_CPP ":""" ))
            } // END
            PAUSE_CPP(( int64_t // int64_t ))
            RESUME_PYTHON ':'''
            ((""":" )) RESUME_CPP ":""" ))
        random.choice(funcs)();
        PAUSE_CPP(( int64_t // int64_t ))
        ''':' PAUSE_PYTHON
        ((""":" )) RESUME_CPP ":""" ))
        } // END
        PAUSE_CPP(( int64_t // int64_t ))
        RESUME_PYTHON ':'''
        ((""":" )) RESUME_CPP ":""" ))
    PAUSE_CPP(( int64_t // int64_t ))
    ''':' PAUSE_PYTHON
    ((""":" )) RESUME_CPP ":""" ))
    } // END
    PAUSE_CPP(( int64_t // int64_t ))
    RESUME_PYTHON ':'''
    ((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))


PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
}; // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
}; // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))
} // END
PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

UNIQUE_IDENTIFIER = """*/"_""";

PAUSE_CPP(( int64_t // int64_t ))
''':' PAUSE_PYTHON
((""":" )) RESUME_CPP ":""" ))

int main(){
    b_set<int> a;
    assert(not a.contains(9));
    a.add(9);
    a.add(8);
    a.add(7);
    a.add(6);
    a.add(5);
    a.add(4);
    assert(a.contains(9));
    assert(a.contains(8));
    assert(a.contains(7));
    assert(a.contains(6));
    assert(a.contains(5));
    assert(a.contains(4));
    assert(not a.contains(3));
    a.remove(9);
    a.remove(7);
    a.remove(5);
    a.remove(3);
    assert(not a.contains(9));
    assert(    a.contains(8));
    assert(not a.contains(7));
    assert(    a.contains(6));
    assert(not a.contains(5));
    assert(    a.contains(4));
    assert(not a.contains(3));
    assert(not a.contains(2));

    a =    b_set<int>();
    std::set<int> s;

    std::mt19937_64 rand;
    for (size_t q = 0; q < 999999; ++q){
        std::vector<std::function<void()>> funcs;
        funcs.push_back([&](){
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&](){
            int w = rand();
            assert(s.count(w) == a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&](){
            auto tmp = a;
            a = tmp;
        });
    }
}

PAUSE_CPP(( int64_t // int64_t ))
RESUME_PYTHON ':'''
((""":" )) RESUME_CPP ":""" ))

