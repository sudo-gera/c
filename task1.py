from __future__ import annotations
import matplotlib.pyplot as plt
import numpy as np
from fractions import Fraction
import math
o=Fraction(1)
import operator
import numbers
import inspect
import functools
from pprint import pprint

power=9
center=2
coef = [*map(round, (np.polynomial.Polynomial([-center, 1])**power).coef)]
def log(f:Fraction):
    f = Fraction(f)
    if f == 0:
        return float('-inf')
    f=abs(f)
    return math.log(f.numerator)-math.log(f.denominator)

max_error = 0

meps = Fraction(1, 2**53)

def op(func_name):
    def op(*a):
        a = [fl(w) for w in a]
        if len(a)==2:
            flf = lambda *a: Fraction(getattr(float, func_name)(*map(float, a)))
            frf = getattr(Fraction, func_name)
            a, d = a
            af, ag, ad = a.f, a.g, a.d
            df, dg, dd = d.f, d.g, d.d
            assert ag - ad * meps * abs(ag) <= af <= ag + ad * meps * abs(ag)
            assert dg - dd * meps * abs(dg) <= df <= dg + dd * meps * abs(dg)
            xf = flf(af, df)
            xg = frf(af, df)
            xd = 1
            assert xg - xd * meps * abs(xg) <= xf <= xg + xd * meps * abs(xg)
            sf = xf
            sg = frf(ag, dg)
            sd = max(ad, dd) + 1

            assert sg-(sd-1)*meps * (abs(ag)+abs(dg)) <= xg <= sg+(sd-1)*meps * (abs(ag)+abs(dg))

            assert sg - sd * meps * abs(sg) <= xg - xd * meps * abs(xg) <= sf <= xg + xd * meps * abs(xg) <= sg + sd * meps * abs(sg)


            assert sg - sd * meps * abs(sg) <= sf <= sg + sd * meps * abs(sg)


            s = fl(dict(f=sf, g=sg, d=sd))
            return s





        f = [w.f for w in a]
        g = [w.g for w in a]
        d = [w.d for w in a]
        s = getattr(Fraction, func_name)(*map(Fraction, f))
        f = getattr(float,    func_name)(*f)
        g = getattr(Fraction, func_name)(*g)
        d = max(d)+1
        assert isinstance(s, Fraction) and isinstance(g, Fraction)
        error = abs(Fraction(f) - s)
        allow = abs(s*meps)
        if not error <= allow:
            print(func_name, a, f, s)
            assert False
        error = abs(Fraction(f) - g)
        allow = abs(g*meps*d)
        if not error <= allow:
            print(func_name, a)
            assert False
        return fl(dict(f=f, g=g, d=d, op=func_name, prev=a))
    return op

# class fl(numbers.Real):
class fl():
    def __init__(self, f:float):
        try:
            if isinstance(f, fl):
                f = f.__dict__
            if isinstance(f, dict):
                self.__dict__.update(f)
                return
            self.f=Fraction(f)
            self.g=Fraction(f)
            self.d=1-isinstance(f, float)
        finally:
            self.check()
    def __repr__(self):
        return repr(self.__dict__)
    def __float__(self):
        return self.f
    def check(self):
        assert isinstance(self.f, Fraction)
        assert isinstance(self.g, Fraction)
        error = abs(Fraction(self.f) - self.g)
        allow = abs(self.d * meps * self.g)
        # assert error <= allow
# for func in ['abs', 'add', 'ceil', 'eq', 'floor', 'floordiv', 'le', 'lt', 'mod', 'mul', 'neg', 'pos', 'pow', 'radd', 'rsub', 'rfloordiv', 'rmod', 'rmul', 'round', 'rpow', 'rtruediv', 'truediv', 'trunc']:
for func in ['add', 'mul']:
    func = f'__{func}__'
    setattr(fl, func, op(func))

def horner(coef, x):
    x=fl(x)
    res = fl(0.0)
    for c in coef[::-1]:
        res *= x
        res += c
    return res
xs = np.linspace(center-0.08, center+0.08, 1000)


# res1 = c_n
# res2 = (res1*x*(1+d)+c_{n-1})*(1+d) = c_n*x*(1+d)^2 + c_{n-1}*(1+d)
# res3 = (res2*x*(1+d)+c_{n-2})*(1+d) = c_n*x^2*(1+d)^4 + c_{n-1}*x*(1+d)^3 + c_{n-2}*(1+d)
# res4 = (res3*x*(1+d)+c_{n-3})*(1+d) = c_n*x^3*(1+d)^6 + c_{n-1}*x^2*(1+d)^5 + c_{n-2}*x*(1+d)^3 + c_{n-3}*(1+d)
# res5 = (res4*x*(1+d)+c_{n-4})*(1+d) = c_n*x^4*(1+d)^8 + c_{n-1}*x^3*(1+d)^7 + c_{n-2}*x^2*(1+d)^5 + c_{n-3}*x*(1+d)^3 + c_{n-4}*(1+d)

# res_k     = c_n*x^(k-1)*(1+d)^(2k-2) + sum i from 1 to k - 1 c_{n-i}*x^(k-1-i)*(1+d)^(2k-1-2i)
# res_{n+1} = c_n*x^(n  )*(1+d)^(2n  ) + sum i from 1 to n     c_{n-i}*x^(n  -i)*(1+d)^(2n+1-2i)
# res_{n+1} = c_n*x^(n)*(1+d)^(2n) + sum i from 0 to n-1 c_i*x^i*(1+d)^(1+2i)
# 2n * d < 1
# res_{n+1} = c_n*x^(n)*(1+d*2n+O(d^2)) + sum i from 0 to n-1 c_i*x^i*(1+d*(1+2i)+O(d^2))
def err(coef, x):
    n = len(coef)-1
    res = coef[n]*x**n*2*n
    for i in range(0, n):
        res += coef[i]*x**i*(1+2*i)
    return abs(res)*float(max_error)

horner_ys = [float(horner(coef, x)) for x in xs]
exact_ys = [(x-center)**power for x in xs]
diff_ys = [abs(y-z) for y,z in zip(exact_ys, horner_ys)]
error_ys = [err(coef, x) for x in xs]
min_ys = [y-e for y,e in zip(exact_ys, error_ys)]
max_ys = [y+e for y,e in zip(exact_ys, error_ys)]

print(diff_ys)
print(error_ys)
print(len([a for a,s,d in zip(diff_ys, error_ys, exact_ys) if s<a]))

plt.figure()
plt.plot(xs,horner_ys)
plt.plot(xs,exact_ys)
plt.plot(xs,min_ys)
plt.plot(xs,max_ys)
plt.show()



