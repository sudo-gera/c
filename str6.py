n,x=[int(w) for w in input().split()]
a=[int(w) for w in input().split()]
a.sort(reverse=1)
from functools import *
@cache
def count(s,d):
    assert d
    assert s%a[d-1]==0
    if d>1:
        assert d>1
        ps=(s//a[d-2]         )*a[d-2]
        z=count(ps,d-1)+abs(s-ps)//a[d-1]
        ps=(s//a[d-2]+bool(s%a[d-2]))*a[d-2]
        x=count(ps,d-1)+abs(s-ps)//a[d-1]
        return min(z,x)
    else:
        assert d==1
        return s//a[d-1]
print(count(x,len(a)))
