import numpy as np
import builtins
from copy import copy

def solve(a: np.ndarray, b: np.ndarray):
    b = copy(b)
    a = copy(a)
    a = a.astype(float)
    n = a.shape[0]
    assert a.shape == (n,n)

    permutations = np.zeros((n-1), int)
    sum_of_ls = np.eye(n)
    p = np.eye(n)

    u = copy(a)
    for i in range(n-1):
        j = np.argmax([*map(abs, u[i:n, i])]) + i
        permutations[i]=j
        p[[i,j], :] = p[[j,i], :]
        u[[i,j], :] = u[[j,i], :]
        b[[i, j]] = b[[j, i]]
        for j in range(i+1, n):
            t = -u[j, i] / u[i, i]
            u[j, :] += u[i, :] * t
            sum_of_ls[j, i] = t


    for i in range(0, n-1):
        j = permutations[i]
        sum_of_ls[[i,j], :i] = sum_of_ls[[j,i], :i]

    l = np.eye(n)
    for i in range(n-1):
        for j in range(i+1, n):
            l[:, i] -= l[:, j] * sum_of_ls[j, i]

    z = np.zeros(n)
    for i in range(n):
        z[i] = (b[i] - np.dot(z[:i], l[i, :i]))/l[i,i]

    x = np.zeros(n)
    for i in range(n)[::-1]:
        x[i] = (z[i] - np.dot(x[i+1:], u[i,i+1:]))/u[i,i]

    return l, u, p, x


def check(a, b):
    l, u, p, x = solve(a, b)
    # assert np.allclose(
    #     l @ u, p @ a
    # )
    # assert np.allclose(
    #     a @ x, b
    # )
    return np.linalg.norm(x - np.linalg.solve(a, b))

z = np.ndarray((50, 4))
for n in range(1, z.shape[0]+1):
    b = np.random.rand(n)+1
    a = np.random.rand(n, n)+1
    z[n-1, :2] = [n, check(a,b)]
    b = np.exp((np.random.rand(n)-0.5)*8)
    a = np.exp((np.random.rand(n, n)-0.5)*8)
    z[n-1, 2:] = [n, check(a,b)]

import matplotlib.pyplot as plt
fig, axs = plt.subplots(2)
axs[0].plot(z[:, 0], z[:, 1])
axs[0].set_title('good numbers')
axs[1].plot(z[:, 2], z[:, 3])
axs[1].set_title('bad numbers')
plt.show()

