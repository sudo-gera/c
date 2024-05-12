import numpy as np
import builtins
from copy import copy

def solve(a: np.ndarray, b: np.ndarray):
    a = a.astype(float)
    n = a.shape[0]
    assert a.shape == (n,n)

    ls = [*map(np.eye, [n]*(n-1))]
    pjs = np.zeros((n-1), int)

    u = copy(a)
    for i in range(n-1):
        j = np.argmax([*map(abs, u[i:n, i])]) + i
        pjs[i]=j
        u[[i,j], :] = u[[j,i], :]
        for j in range(i+1, n):
            t = -u[j, i] / u[i, i]
            u[j] += u[i] * t
            ls[i][j, i] = t

    ks = [*map(copy, ls)]

    for i in range(n-1)[::-1]:
        for k in range(i+1, n-1):
            kj = pjs[k]
            ks[i][[k,kj],i] = ks[i][[kj,k],i]

    p = np.eye(n)
    for i in range(n-1):
        j = pjs[i]
        p[[i,j], :] = p[[j,i], :]

    r = np.eye(n)
    for i in range(n-1):
        for b in range(i+1, n):
            assert isinstance(ks[i][b, i], float)
            r[:, i] -= r[:, b] * ks[i][b, i]

    assert np.allclose(p @ a, r @ u)
    for z in range(n):
        for x in range(n):
            assert np.allclose(r[z,x], 0) and z<x or z>=x
            assert np.allclose(u[z,x], 0) and z>x or z<=x



a = np.random.rand(4, 4)
solve(a, None)
a = np.random.rand(8, 8)
solve(a, None)
