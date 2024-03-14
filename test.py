from __future__ import annotations;
from typing import TypeVar, Generic, Self, Callable, Optional as Option;


K = TypeVar('K');
V = TypeVar('V');


class Item(Generic[V]):
    def __init__(self: Item[V], v: Option[V]):
        self.newer: int = 0;
        self.older: int = 0;
        self.val: Option[V] = v;

    def __repr__(self: Item[V]) -> str:
        val = self.val;
        older = self.older;
        newer = self.newer;
        return f'({val = } {older = } {newer = })';

def add(left: Item[V], lkey: int,
        right: Item[V], rkey: int) -> None:
    left.newer = rkey;
    right.older = lkey;

def sub(left: Item[V], lkey: int,
        right: Item[V], rkey: int) -> None:
    left.newer = lkey;
    right.older = rkey;

class Cache(Generic[K, V]):
    def __init__(self, c: int):
        self.counter: int = 0;
        self.capacity: int = c;
        self.keys: dict[K, int] = {};
        self.data: dict[int, Item[V]] = {};
        self.root : Item[V] = Item(None);
        self.check();

    def data_get(self, k: int) -> Item[V]:
        if k == 0:
            return self.root
        return self.data[k]

    def extract(self, it: Item[V], key: int) -> None:
        self.check();
        okey, nkey = it.older, it.newer;
        older, newer = self.data_get(okey), self.data_get(nkey);
        sub(older, okey, it, key);
        sub(it, key, newer, nkey);
        add(older, okey, newer, nkey);
        del self.data[key];
        self.check();

    def insert_as_newest(self, it: Item[V], key: int) -> None:
        self.check();
        nkey = self.root.newer;
        newer = self.data_get(nkey);
        okey = 0;
        older = self.root;
        sub(older, okey, newer, nkey);
        add(older, okey, it, key);
        add(it, key, newer, nkey);
        self.data[key] = it;
        self.check();

    def key_to_int(self, key: K) -> int:
        if len(self.keys) > len(self.data) * 2:
            self.keys = {k:v for k,v in self.keys.items() if v in self.data}
        if key not in self.keys:
            self.counter += 1
            self.keys[key] = self.counter
        return self.keys[key]

    def get(self, key: K) -> Option[V]:
        k = self.key_to_int(key)
        self.check();
        if k in self.data:
            it = self.data[k];
            self.extract(it, k);
            self.insert_as_newest(it, k);
            return it.val;
        return None;

    def set(self, key: K, v: V) -> Option[V]:
        k = self.key_to_int(key)
        self.check();
        if k in self.data:
            it = self.data[k];
            self.extract(it, k);
            self.insert_as_newest(Item(v), k);
            self.check();
            return it.val;
        if len(self.data) == self.capacity:
            older = self.root.older;
            assert older != 0;
            self.extract(self.data_get(self.root.older), older);
        self.insert_as_newest(Item(v), k);
        self.check();
        return None;

    def check(self: Self) -> None:
        assert(len(self.data) * 2 >= len(self.keys) - 4)
        it: Item[V] = self.root;
        its = [];
        while True:
            its.append(it);
            assert (it != self.data_get(self.root.newer)) ^ (self.data_get(it.older) is self.root);
            assert (it != self.data_get(self.root.older)) ^ (self.data_get(it.newer) is self.root);
            assert self.data_get(self.data_get(it.older).newer) is it;
            it = self.data_get(it.older);
            if it is self.root:
                break;
        assert len(set(map(id, its))) == len(set(map(id, its)));
        assert self.capacity + 1 >= len(self.data)+1 == len(its);
        assert sorted([*self.data.values(), self.root], key=id) == sorted(its, key=id);

class SimpleCache(Generic[K, V]):
    def __init__(self: SimpleCache[K,V], capacity: int) -> None:
        self.data : dict[K,V] = {}
        self.capacity = capacity
    def get(self: SimpleCache[K,V], k: K) -> V|None:
        if k not in self.data:
            return None
        v = self.data[k]
        del self.data[k]
        self.data[k] = v
        return v
    def set(self: SimpleCache[K,V], k: K, v: V) -> V|None:
        if k in self.data:
            ov = self.data[k]
            del self.data[k]
            self.data[k] = v
            return ov
        if len(self.data) == self.capacity:
            del self.data[next(iter(self.data))]
        self.data[k] = v
        return None

c: Cache[int, int] = Cache(2);
assert c.set(1, 11) is None;
assert c.set(2, 21) is None;
assert c.set(1, 12) == 11;
assert c.get(1) == 12;
assert c.get(2) == 21;
assert c.get(1) == 12;
assert c.get(2) == 21;
assert c.set(3, 31) is None;
assert c.get(1) is None;
assert c.get(2) == 21;
assert c.get(3) == 31;

c = Cache(1);
assert c.set(1, 11) is None;
assert c.set(2, 21) is None;
assert c.set(1, 12) is None;
assert c.get(1) == 12;
assert c.get(2) is None;
assert c.get(1) == 12;
assert c.get(2) is None;
assert c.set(3, 31) is None;
assert c.get(1) is None;
assert c.get(2) is None;
assert c.get(3) == 31;

import random

oc : Cache[int, int] = Cache(99)
sc : SimpleCache[int, int] = SimpleCache(99)
for q in range(500_0):
    if random.randint(0,2):
        k = random.randint(0, 300)
        v = random.randint(0, 300)
        assert sc.set(k, v) == oc.set(k,v)
    else:
        k = random.randint(0, 300)
        assert sc.get(k) == oc.get(k)
        
