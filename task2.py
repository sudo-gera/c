import numpy as np
import builtins
from copy import copy

def solve(a: np.ndarray, b: np.ndarray):
    a = a.astype(float)
    n = a.shape[0]
    assert a.shape == (n,n)

    ps = [*map(np.eye, [n]*(n-1))]
    ls = [*map(np.eye, [n]*(n-1))]
    pjs = np.zeros((n-1), int)

    u = copy(a)
    for i in range(n-1):
        j = np.argmax([*map(abs, u[i:n, i])]) + i
        pjs[i]=j
        ps[i][i, i]=0
        ps[i][j, j]=0
        ps[i][j, i]=1
        ps[i][i, j]=1
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

    rs = [*map(np.linalg.inv, ks)]

    for i in range(n-1):
        assert (rs[i]+ks[i] == np.eye(n)*2).all()

    r = np.eye(n)
    for i in range(n-1):
        for b in range(i+1, n):
            r[:, i] -= r[:, b] * ks[i][b, i]

        # r = r @ rs[i]

    import operator
    import functools

    assert np.allclose(
        p, functools.reduce(operator.matmul, ps[::-1])
    )

    assert np.allclose(
        r, functools.reduce(operator.matmul, rs)
    )

    assert np.allclose(
        functools.reduce(operator.matmul, map(functools.partial(functools.reduce, operator.matmul), zip(ls[::-1], ps[::-1]))),
        functools.reduce(operator.matmul, ks[::-1]) @ functools.reduce(operator.matmul, ps[::-1])
    )

    assert np.allclose(functools.reduce(operator.matmul, ks[::-1]) @ functools.reduce(operator.matmul, ps[::-1]) @ a, u)
    assert np.allclose(functools.reduce(operator.matmul, ps[::-1]) @ a, functools.reduce(operator.matmul, rs) @ u)
    assert np.allclose(p @ a, functools.reduce(operator.matmul, rs) @ u)
    assert np.allclose(p @ a, r @ u)
    for z in range(n):
        for x in range(n):
            assert np.allclose(r[z,x], 0) and z<x or z>=x
            assert np.allclose(u[z,x], 0) and z>x or z<=x



a = np.random.rand(4, 4)
solve(a, None)
a = np.random.rand(8, 8)
solve(a, None)
