<<<<<<< HEAD
from copy import copy
=======
from numpy import copy
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
import numpy as np
import operator
import random
import time
<<<<<<< HEAD
=======
import numba
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314

def matmul(A: np.ndarray, B: np.ndarray):
    assert len(A.shape) == len(B.shape) == 2
    assert A.shape[1] == B.shape[0]

<<<<<<< HEAD
    return A @ B
=======
    # return A @ B
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
    C = np.zeros((A.shape[0], B.shape[1]))
    for q in range(A.shape[0]):
        for w in range(A.shape[1]):
            for e in range(B.shape[1]):
                C[q, e] += A[q, w] * B[w, e]
    return C

<<<<<<< HEAD

def subst(L: np.ndarray, b: np.ndarray):
    n = A.shape[0]
    assert A.shape == (n,n)
    assert b.shape in [(n,), (n, 1)]

    return np.linalg.inv(L) @ b
=======
def subst(L: np.ndarray, b: np.ndarray):
    n = A.shape[0]
    assert A.shape == (n,n)
    assert b.shape == (n, 1)

    # return np.linalg.inv(L) @ b
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
    z = np.zeros(n)
    for i in range(n):
        res = 0
        for j in range(i):
            res += z[j] * L[i, j]
        z[i] = (b[i][0] - res)/L[i,i]
    return z.reshape((n, 1))

<<<<<<< HEAD

def solve(A: np.ndarray, b: np.ndarray, max_iter: int, tol: float):
    n = A.shape[0]
    assert A.shape == (n,n)
    assert b.shape in [(n,), (n, 1)]
=======
def solve(A: np.ndarray, b: np.ndarray, max_iter: int, tol: float):
    n = A.shape[0]
    assert A.shape == (n,n)
    assert b.shape == (n,)
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
    b = b.reshape((n, 1))

    L = copy(A)
    D = copy(A)
    U = copy(A)
    for q in range(n):
        for w in range(n):
            q < w  or operator.setitem(U, (q,w), 0)
            q == w or operator.setitem(D, (q,w), 0)
            q > w  or operator.setitem(L, (q,w), 0)

    assert (A == L + D + U).all()

<<<<<<< HEAD
    x = np.array([0]*n).reshape((n, 1))

    ld = L+D

    diff = []
    for iter_num in range(max_iter):
        diff.append(np.linalg.norm(matmul(A, x) - b))
        if diff[-1] < tol:
=======
    x = np.array([0.]*n).reshape((n, 1))

    ld = L+D

    diff = [0]*n
    for iter_num in range(max_iter):
        diff[iter_num] = (np.linalg.norm(matmul(A, x) - b))
        if diff[iter_num] < tol:
            diff = diff[:iter_num+1]
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
            break
        x = -subst(ld, matmul(U, x)) + subst(ld, b)
    return x, diff

def create_positive_defined_matrix(n):
    while 1:
        A = np.array(
            [
                [
<<<<<<< HEAD
                    random.random() + 9 * (q==w)
=======
                    random.random() + 400.3 * (q==w)
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
                for q in range(n)]
            for w in range(n)]
        )
        A += A.T
        eigvals = np.linalg.eigvals(A)
        if (0 < eigvals).all():
<<<<<<< HEAD
=======
            # A /= max(eigvals)
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
            break
    return A

n=111
A = create_positive_defined_matrix(n)
<<<<<<< HEAD
=======
print(f'{np.linalg.cond(A) = }')
eigvals = np.linalg.eigvals(A)
# print(f'{min(eigvals) = } {max(eigvals) = }')
# print(f'{min(A.diagonal()) = }')
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314
b = np.array([random.random() for q in range(n)])
t1 = time.perf_counter()
x, diff = solve(A, b, 99, 10**-12)
x = x.reshape(n)
t2 = time.perf_counter()
xx = np.linalg.solve(A, b)
t3 = time.perf_counter()
print(f'{len(diff) = }')
print(f'{np.linalg.norm(x-xx) = }')
print(f'{t3 - t2 = :40.40f}')
print(f'{t2 - t1 = :40.40f}')

<<<<<<< HEAD
# import matplotlib.pyplot as plt
# plt.plot([*range(len(diff))], np.log(diff))
# plt.show()
=======
import matplotlib.pyplot as plt
plt.plot([*range(len(diff))], np.log(diff))
plt.show()
>>>>>>> 16f0490d379a59fd603b73d447a82c883e9ab314


