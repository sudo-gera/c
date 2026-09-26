from __future__ import annotations
from fractions import Fraction
from dataclasses import *

@dataclass(frozen=True)
class Expr:
    mul: Fraction
    add: Fraction

    def __mul__(self, value: Fraction | int) -> Expr:
        value = Fraction(value)
        return Expr(
            self.mul * value,
            self.add * value,
        )

    def __rmul__(self, value: Fraction | int) -> Expr:
        return self * value

    def __truediv__(self, value: Fraction | int) -> Expr:
        value = 1 / Fraction(value)
        return self * value

    def __add__(self, value: Fraction | int) -> Expr:
        value = Fraction(value)
        return Expr(
            self.mul,
            self.add + value,
        )

    def __radd__(self, value: Fraction | int) -> Expr:
        return self + value

    def __mod__(self, value: Fraction | int) -> Fraction:
        value = Fraction(value)
        if self.mul % value == 0:
            return self.add % value
        else:
            raise TabError

    def __floordiv__(self, val: Expr) -> Expr:
        mul = self.mul / val.mul
        add = self.add - mul * val.add
        return Expr(mul, add)
    
def divizor(expr: Expr) -> Expr:
    original = expr
    try:
        while True:
            if expr % 2 == 0:
                expr = expr / 2
            else:
                expr = expr * 3 + 1
    except TabError:
        return expr
        # return expr // original

def to_radix_list(value: int, base: int) -> list[int]:
    z=abs(value)
    x=z
    if bin(base).count('1')==1:
        s=list(bin(z)[2:][::-1])
        s=[int(w) for w in s]
        l=len(bin(base))-3
        while len(s)%l:
            s.append(0)
        r=[]
        s=s[::-1]
        for w in range(0,len(s),l):
            a=0
            for t in range(l):
                a*=2
                a+=s[w+t]
            r.append(a)
        if not r:
            r=[0]
        s=r
    else:
        s=[]
        while z:
            s.append(z%base)
            z//=base
        if not s:
            s=[0]
        s=s[::-1]
    if value<0:
        s = [-w for w in s]
    return s

def to_radix(q: int, e: int) -> str:
    s=to_radix_list(q,e)
    s=''.join(["0123456789abcdefghijklmnopqrstuvwxyz".upper()[w] for w in s])
    return s

modulo = 8

for i in range(modulo):
    f = divizor(Expr(modulo, i))
    assert int(f.mul) == f.mul
    assert int(f.add) == f.add
    a=f"{to_radix(modulo, 2):0>8} * k + {to_radix(i, 2):0>8}   ->    {to_radix(int(f.mul), 3):0>8s} * k + {to_radix(int(f.add), 3):0>12s}"
    a=''.join(
        [
            '\x1b[90m0\x1b[0m'
                if c == '0' else
            '\x1b[92m1\x1b[0m'
                if c == '1' else
            '\x1b[96m2\x1b[0m'
                if c == '2' else
            c
            for c in a
        ]
    )
    print(a)










