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
        self.data: dict[Option[K], Item[K, V]] = {};
        self.data[None] = Item(None);
        self.check();


    def extract(self, it: Item[K, V], key: K) -> None:
        self.check();
        okey, nkey = it.older, it.newer;
        older, newer = self.data[okey], self.data[nkey];
        older.sub(okey, it, key);
        it.sub(key, newer, nkey);
        older.add(okey, newer, nkey);
        del self.data[key];
        self.check();

    def insert_as_newest(self, it: Item[K, V], key: K) -> None:
        self.check();
        nkey = self.data[None].newer;
        newer = self.data[self.data[None].newer];
        okey = None;
        older = self.data[None];
        older.sub(okey, newer, nkey);
        older.add(okey, it, key);
        it.add(key, newer, nkey);
        self.data[key] = it;
        self.check();

    def get(self, k: K) -> Option[V]:
        self.check();
        it = self.data.get(k, None);
        if it is not None:
            self.extract(it, k);
            self.insert_as_newest(it, k);
            return it.val;
        return None;

    def set(self, k: K, v: V) -> Option[V]:
        self.check();
        it = self.data.get(k, None);
        if it is not None:
            self.extract(it, k);
            self.insert_as_newest(Item(v), k);
            self.check();
            return it.val;
        else:
            if len(self.data) == self.capacity + 1:
                older = self.data[None].older;
                assert older is not None;
                self.extract(self.data[self.data[None].older], older);
            self.insert_as_newest(Item(v), k);
            self.check();
            return None;

    def check(self: Self) -> None:
        it: Item[K, V] = self.data[None];
        its = [];
        while True:
            its.append(it);
            assert (it != self.data[self.data[None].newer]) ^ (self.data[it.older] is self.data[None]);
            assert (it != self.data[self.data[None].older]) ^ (self.data[it.newer] is self.data[None]);
            assert self.data[self.data[it.older].newer] is it;
            it = self.data[it.older];
            if it is self.data[None]:
                break;
        assert len(set(map(id, its))) == len(set(map(id, its)));
        assert self.capacity + 1 >= len(self.data) == len(its);
        assert sorted([*self.data.values()], key=id) == sorted(its, key=id);


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


