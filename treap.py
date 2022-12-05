from __future__ import annotations
import copy
import dataclasses
import time
import random
import typing
import traceback
import json
import functools

class treap:
    @dataclasses.dataclass
    class no_copy:
        val: typing.Union[treap,None] = None
        step: int = 1 # only -1 or 1

    def __init__(self, l=[]) -> None:
        ...

    def __len__(self) -> int:
        ...

    def cut_left(self, n) -> treap:
        ...

    def cut_right(self, n) -> treap:
        ...

    def add_left(self, oth) -> None:
        ...

    def add_right(self, oth) -> None:
        ...

    def __getitem__(self, n: typing.Union[int , slice]):
        ...

    def __setitem__(self, n: typing.Union[int , slice], v) -> None:
        ...

    def __delitem__(self, n: typing.Union[int , slice], v) -> None:
        ...

    def __iter__(self) -> iter:
        ...

    def __repr__(self) -> str:
        ...

    def __cmp__(self, oth):
        ...

    def __lt__(self, oth):
        ...

    def __gt__(self, oth):
        ...

    def __le__(self, oth):
        ...

    def __ge__(self, oth):
        ...

    def __eq__(self, oth):
        ...

    def __ne__(self, oth):
        ...

    def __copy__(self):
        ...

    def __deepcopy__(self, d):
        ...

    def sort(self, *args, **kwargs):
        ...

    def reverse(self):
        ...

    def index(self, v, start=0, stop=None):
        ...

    def remove(self, v):
        ...

    def pop(self, v):
        ...

    def insert(self, n, v):
        ...

    def extend(self, v):
        ...

    def count(self, value):
        ...

    def copy(self):
        ...

    def clear(self):
        ...

    def append(self, val):
        ...

    def __iadd__(self, oth):
        ...

    def __add__(self, oth):
        ...

    def __radd__(self, oth):
        ...

    def __imul__(self,n:int):
        ...

    def __mul__(self,n:int):
        ...

    def __rmul__(self,n:int):
        ...













    @dataclasses.dataclass
    class node:
        x: typing.Any
        _left: treap.Node = None
        y: float = dataclasses.field(default_factory=random.random)
        _right: treap.Node = None
        parent: treap.Node = None
        size: int = 1
        rev: int = 0

        @property
        def left(self):
            treap.check[0](self)
            treap.make(self._left)
            return self._left

        @left.setter
        def left(self, value):
            self._left = value
            treap.update(self)
            treap.check[0](self)

        @property
        def right(self):
            treap.make(self._right)
            treap.check[0](self)
            return self._right

        @right.setter
        def right(self, value):
            self._right = value
            treap.update(self)
            treap.check[0](self)
    Node = typing.Union[node , None]

    check = [lambda a:0]

    @staticmethod
    def update(q: Node) -> None:
        if q is None:
            return
        if q._left is not None and q._right is not None:
            q.size = q._left.size + 1 + q._right.size
            q._left.parent = q
            q._right.parent = q
        elif q._right is not None:
            q.size = 1 + q._right.size
            q._right.parent = q
        elif q._left is not None:
            q.size = 1 + q._left.size
            q._left.parent = q
        else:
            q.size = 1

    @staticmethod
    def make(q: Node) -> None:
        if q is None:
            return
        if q.rev:
            q._left, q._right = q._right, q._left
            if q._left is not None:
                q._left.rev ^= 1
            if q._right is not None:
                q._right.rev ^= 1
            q.rev = 0

    @staticmethod
    def merge(q: Node, e: Node) -> Node:
        if q is None:
            return e
        elif e is None:
            return q
        elif q.y > e.y:
            q.right = treap.merge(q.right, e)
            return q
        else:
            e.left = treap.merge(q, e.left)
            return e

    @staticmethod
    def split(q: Node, n: int) -> tuple[Node, Node]:
        if q is None:
            return (None, None)
        if n <= 0:
            return (None, q)
        if q.size <= n:
            return (q, None)
        ls = q.left.size if q.left is not None else 0
        if n <= ls:
            e, q.left = treap.split(q.left, n)
            if e is not None:
                e.parent = None
            return (e, q)
        else:
            q.right, e = treap.split(q.right, n-ls-1)
            if e is not None:
                e.parent = None
            return (q, e)

    @staticmethod
    def l(q: Node) -> int:
        if q is None:
            return 0
        return q.size

    @staticmethod
    def next(q: Node, n: int) -> Node:
        l = treap.l
        if q is None:
            return None
        while q.parent is not None and not -l(q.left) <= n <= l(q.right):
            if q is q.parent.left:
                n -= l(q.right)+1
            else:
                n += l(q.left)+1
            q = q.parent
        if not -l(q.left) <= n <= l(q.right):
            return None
        if 0 < n:
            if q is None:
                return None
            return treap.next(q.right, n-1-l(q.right.left))
        if n < 0:
            if q is None:
                return None
            return treap.next(q.left, n+1+l(q.left.right))
        return q

    def __init__(self, l=[]) -> None:
        self._root: treap.Node
        if isinstance(l, treap.node ) or l is None:
            self._root = l
            return
        if isinstance(l, treap.no_copy):
            if l.val is not None:
                self._root = l.val.root
                l.val.root = None
            if l.step == -1:
                self.reverse()
            return
        self._root = None
        for w in l:
            self._root = treap.merge(self._root, treap.node(x=w))

    @property
    def root(self):
        treap.make(self._root)
        return self._root

    @root.setter
    def root(self, v):
        assert isinstance(v, treap.node) or v is None
        self._root = v

    def getnode(self, n: int) -> Node:
        t = None
        if self.root is not None:
            t = treap.next(self.root, -treap.l(self.root.left)+n)
        return t

    def __len__(self) -> int:
        return self.root.size if self.root is not None else 0

    def cut_left(self, n) -> treap:
        r, self.root = treap.split(self.root, n)
        return treap(r)

    def cut_right(self, n) -> treap:
        self.root, r = treap.split(self.root, len(self)-n)
        return treap(r)

    def add_left(self, oth) -> None:
        self.root = treap.merge(oth.root, self.root)
        oth.root = None

    def add_right(self, oth) -> None:
        self.root = treap.merge(self.root, oth.root)
        oth.root = None

    def prettyslice(self, n: slice) -> slice:
        if isinstance(n.step, int) and n.step < 0 or isinstance(n.step, treap.no_copy) and n.step.step < 0:
            return slice(
                len(self)-1 if n.start is None else n.start +
                len(self) if n.start < 0 else n.start,
                -1 if n.stop is None else n.stop +
                len(self) if n.stop < 0 else n.stop,
                1 if n.step is None else n.step,
            )
        else:
            return slice(
                0 if n.start is None else n.start +
                len(self) if n.start < 0 else n.start,
                len(self) if n.stop is None else n.stop +
                len(self) if n.stop < 0 else n.stop,
                1 if n.step is None else n.step,
            )

    def __getitem__(self, n: typing.Union[int , slice]):
        if isinstance(n, slice):
            n = self.prettyslice(n)
            if n.step in [1, -1, treap.no_copy] or isinstance(n.step, treap.no_copy):
                nn = slice(n.stop+1, n.start+1, n.step) if n.step == - \
                    1 or isinstance(n.step, treap.no_copy) and n.step.step == -1 else n
                r2 = self.cut_left(nn.stop)
                r1 = r2.cut_left(nn.start)
                t = r2
                if n.step == treap.no_copy or isinstance(n.step, treap.no_copy):
                    r2 = treap()
                    if isinstance(n.step, treap.no_copy) and n.step.step == -1:
                        t.reverse()
                else:
                    r2 = treap(t)
                    if n.step == -1:
                        t.reverse()
                self.add_left(r2)
                self.add_left(r1)
                return t
            else:
                t = treap()
                p = self.getnode(n.start)
                w = n.start
                while w in range(n.start, n.stop, n.step):
                    if p is not None:
                        t.append(p.x)
                        p = treap.next(p, n.step)
                        w += n.step
                    else:
                        p = self.getnode(w)
                return t
        else:
            cn = self.getnode(n)
            if cn is not None:
                return cn.x
            else:
                raise IndexError

    def __setitem__(self, n: typing.Union[int , slice], v) -> None:
        if isinstance(n, slice):
            n = self.prettyslice(n)
            if n.step in [1, -1, treap.no_copy] or isinstance(n.step, treap.no_copy):
                nn = slice(n.stop+1, n.start+1, n.step) if n.step == - \
                    1 or isinstance(n.step, treap.no_copy) and n.step.step == -1 else n
                r2 = self.cut_left(nn.stop)
                r1 = r2.cut_left(nn.start)
                r2 = v
                if n.step == treap.no_copy or isinstance(n.step, treap.no_copy):
                    assert isinstance(r2, treap)
                    if isinstance(n.step, treap.no_copy) and n.step.step == -1:
                        r2.reverse()
                else:
                    r2 = treap(r2)
                    if n.step == -1:
                        r2.reverse()
                self.add_left(r2)
                self.add_left(r1)
            else:
                t = treap()
                p = self.getnode(n.start)
                w = n.start
                vi = iter(v)
                while w in range(n.start, n.stop, n.step):
                    if p is not None:
                        try:
                            p.x = next(vi)
                        except StopIteration:
                            break
                        p = treap.next(p, n.step)
                        w += n.step
                    else:
                        w += n.step
                        p = self.getnode(w)
        else:
            cn = self.getnode(n)
            if cn is not None:
                cn.x = v
            else:
                raise IndexError

    def __delitem__(self, n: typing.Union[int , slice]) -> None:
        if isinstance(n, slice):
            n = self.prettyslice(n)
            if n.step == 1:
                r2 = self.cut_left(n.stop)
                r1 = r2.cut_left(n.start)
                r2 = treap()
                self.add_left(r2)
                self.add_left(r1)
            else:
                for w in zip(range(n.start, n.stop, n.step)):
                    if w in range(len(self)):
                        del self[w]
        else:
            if n not in range(len(self)):
                raise IndexError
            del self[n:n+1]

    @dataclasses.dataclass
    class iter:
        pos: treap.Node
        root: treap

        def __next__(self):
            if self.pos is None:
                raise StopIteration
            var = self.pos.x
            self.pos = treap.next(self.pos, 1)
            return var

    def __iter__(self) -> iter:
        return treap.iter(
            pos=self.getnode(0),
            root=self
        )

    def __repr__(self) -> str:
        return 'treap('+repr(list(self))+')'

    def __cmp__(self, oth):
        if type(self) != type(oth):
            return float('nan')
        for a, s in zip(self, oth):
            if a != s:
                return (a > s)-(a < s)
        return (len(self) > len(oth))-(len(self) < len(oth))

    def __lt__(self, oth): return self.__cmp__(oth) < 0
    def __gt__(self, oth): return self.__cmp__(oth) > 0
    def __le__(self, oth): return self.__cmp__(oth) <= 0
    def __ge__(self, oth): return self.__cmp__(oth) >= 0
    def __eq__(self, oth): return self.__cmp__(oth) == 0
    def __ne__(self, oth): return self.__cmp__(oth) != 0

    def __copy__(self):
        return treap(self)

    def __deepcopy__(self, d):
        t = treap()
        d[id(self)] = t
        for w in self:
            t.append(copy.deepcopy(w, d))
        return t

    def sort(self, *args, **kwargs):
        g = self.getnode(0)
        t = []
        r = []
        while g is not None:
            r.append(g)
            t.append(g.x)
            g = treap.next(g, 1)
        t.sort(*args, **kwargs)
        for w in range(len(t)):
            r[w].x = t[w]

    def reverse(self):
        if self.root is not None:
            self.root.rev ^= 1

    def index(self, v, start=0, stop=None):
        if stop == None:
            stop = len(self)
        if start < 0:
            start = 0
        g = self.getnode(start)
        w = 0
        while w in range(start, stop) and g is not None:
            if g.x == v:
                return w
            g = treap.next(g, 1)
            w += 1
        raise ValueError

    def remove(self, v):
        del self[self.index(v)]

    def pop(self, v):
        t, self[-1:] = self[-1], []
        return t

    def insert(self, n, v):
        self[n:n] = [v]

    def extend(self, v):
        self[len(self):len(self)] = v
        return self

    def count(self, value):
        g = self.getnode(0)
        c = 0
        while g is not None:
            if g.x == value:
                c += 1
            g = treap.next(g, 1)
        return c

    def copy(self):
        return treap(self)

    def clear(self):
        self.root = None

    def append(self, val):
        self.extend([val])

    def __iadd__(self, oth):
        return self.extend(oth)

    def __add__(self, oth):
        return treap(self).extend(treap(oth))

    def __radd__(self, oth):
        return treap(oth).extend(treap(self))

    def __imul__(self,n:int):
        r=treap()
        for w in range(n):
            r+=self
        self.root=r.root
        return self

    def __mul__(self,n:int):
        return treap(self).__imul__(n)

    def __rmul__(self,n:int):
        return treap(self).__imul__(n)


if __name__ == '__main__': # tests
    big_prime=4099
    sml_prime=257
    t=treap(range(big_prime))
    assert list(t)==list(range(big_prime))
    for w in range(len(t)):
        t[w]*=sml_prime
        t[w]%=big_prime
    t.sort()
    assert list(t)==list(range(big_prime))
    for w in range(big_prime):
        t+=treap.no_copy(t[:sml_prime:treap.no_copy])
    assert list(t)==list(range(big_prime))
    t.reverse()
    assert list(t)==list(range(big_prime))[::-1]
    t.reverse()
    assert list(t)==list(range(big_prime))
    for w in range(len(t)):
        z=t[sml_prime-1::treap.no_copy(step=-1)]
        x=t[::treap.no_copy(step=-1)]
        z+=treap.no_copy(x)
        t[::treap.no_copy(step=-1)]=z
    assert list(t)==list(range(big_prime))
    assert list(t[::2]) == list(range(0,big_prime,2))
    for w in range(sml_prime):
        z=random.randint(sml_prime,big_prime-sml_prime-1)
        x=z+random.randint(-sml_prime,sml_prime)
        assert list(t[z:x:2])  == list(range(z,x,2))
        assert list(t[z:x:-2]) == list(range(z,x,-2))
        assert list(t[z:x:1])  == list(range(z,x,1))
        assert list(t[z:x:-1]) == list(range(z,x,-1))
    t[0]=t
    y=copy.deepcopy(t)
    assert y[0] is y
    y[0]=0
    assert t[0] is t
    t[0] = 0
    assert list(t)==list(range(big_prime))
    for w in range(len(t)):
        t[w]=treap([t[w]])
    y=copy.deepcopy(t)
    for w in t:
        w[0]*=-1
    for q,w in zip(y,t):
        assert q[0]+w[0]==0
    t=treap(range(64))
    assert list(t*16) == list(range(64))*16
    for q,w in enumerate(t):
        assert q==w
    y=copy.deepcopy(t)
    y+=treap.no_copy(t)
    assert len(t)==0
