from copy import copy
import numpy as np
import operator
import random

def solve(A: np.ndarray, b: np.ndarray, max_iter: int, tol: float):
    n = A.shape[0]
    assert A.shape == (n,n)

    L = copy(A)
    D = copy(A)
    U = copy(A)
    for q in range(n):
        for w in range(n):
            q < w  or operator.setitem(U, (q,w), 0)
            q == w or operator.setitem(D, (q,w), 0)
            q > w  or operator.setitem(L, (q,w), 0)

    x = np.array([0]*n)

    ld = np.linalg.inv(L+D)

    b = []
    for iter_num in range(max_iter):
        b.append(np.linalg.norm(A @ x - b))
        if b[-1] < tol:
            break
        x = -ld @ U @ x + ld @ b
    return x, b

while 1:
    n=111
    A = np.array(
        [
            [
                random.random()+1
            for q in range(n)]
        for w in range(n)]
    )
    if (np.linalg.det(A) != 0).all():
        break


