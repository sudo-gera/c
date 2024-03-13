from __future__ import annotations;
from typing import TypeVar, Generic, Self, Callable, Optional as Option;


K = TypeVar('K');
V = TypeVar('V');


class Item(Generic[K, V]):
    def __init__(self: Item[K, V], v: Option[V]):
        self.newer: Option[K] = None;
        self.older: Option[K] = None;
        self.val: Option[V] = v;

    def add(self: Item[K, V], skey: Option[K],
            oth: Item[K, V], okey: Option[K]) -> None:
        self.newer = okey;
        oth.older = skey;

    def sub(self: Item[K, V], skey: Option[K],
            oth: Item[K, V], okey: Option[K]) -> None:
        self.newer = skey;
        oth.older = okey;

    def __repr__(self: Item[K, V]) -> str:
        val = self.val;
        older = self.older;
        newer = self.newer;
        return f'({val = } {older = } {newer = })';

class Cache(Generic[K, V]):
    def __init__(self, c: int):
        self.capacity: int = c;
        self.data: dict[K, Item[K, V]] = {};
        self.root : Item[K,V] = Item(None);
        self.check();

    def data_get(self, k: Option[K]) -> Item[K, V]:
        if k is None:
            return self.root
        return self.data[k]

    def extract(self, it: Item[K, V], key: K) -> None:
        self.check();
        okey, nkey = it.older, it.newer;
        older, newer = self.data_get(okey), self.data_get(nkey);
        older.sub(okey, it, key);
        it.sub(key, newer, nkey);
        older.add(okey, newer, nkey);
        del self.data[key];
        self.check();

    def insert_as_newest(self, it: Item[K, V], key: K) -> None:
        self.check();
        nkey = self.root.newer;
        newer = self.data_get(nkey);
        okey = None;
        older = self.root;
        older.sub(okey, newer, nkey);
        older.add(okey, it, key);
        it.add(key, newer, nkey);
        self.data[key] = it;
        self.check();

    def get(self, k: K) -> Option[V]:
        self.check();
        if k in self.data:
            it = self.data[k];
            self.extract(it, k);
            self.insert_as_newest(it, k);
            return it.val;
        return None;

    def set(self, k: K, v: V) -> Option[V]:
        self.check();
        if k in self.data:
            it = self.data[k];
            self.extract(it, k);
            self.insert_as_newest(Item(v), k);
            self.check();
            return it.val;
        else:
            if len(self.data) == self.capacity:
                older = self.root.older;
                assert older is not None;
                self.extract(self.data_get(self.root.older), older);
            self.insert_as_newest(Item(v), k);
            self.check();
            return None;

    def check(self: Self) -> None:
        it: Item[K, V] = self.root;
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


