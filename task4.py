import numpy as np

def interpolate(xs: np.ndarray, fs: np.ndarray, qs: np.ndarray):
    n = xs.shape[0]
    assert xs.shape == fs.shape == (n,)
    
    table = np.eye(n)
    for i in range(n):
        table[i,n-1-i]=fs[i]
    for i in range(n)[::-1]:
        for j in range(n-1-i)[::-1]:
            table[i, j] = (table[i, j+1] - table[i+1, j])/(xs[i] - xs[n-1-j])

    res = np.zeros((qs.shape[0], 2))

    pol = [table[0, 0]]

    for i in range(1, n):
        pol = list(np.array([0] + pol) - np.array(pol + [0]) * xs[n-1-i])
        pol[0] += table[0, i]

    der = [i*c for i,c in enumerate(pol)][1:]

    for i in range(qs.shape[0]):
        res[i, 0] = np.dot([*map(qs[i].__pow__, range(len(pol)))], pol)
        res[i, 1] = np.dot([*map(qs[i].__pow__, range(len(der)))], der)

    return res

nodes_for_plot = np.linspace(-1, 1, 999)

nodes_for_int_count = 15
nodes_for_uniform_int = np.linspace(-1, 1, nodes_for_int_count)
nodes_for_Chebyshev_int = np.cos((np.arange(nodes_for_int_count)+0.5)/nodes_for_int_count*np.pi)

fun = lambda x: np.sin(9*x)
der = lambda x: np.cos(9*x)*9

uniform_int_values = interpolate(nodes_for_uniform_int, fun(nodes_for_uniform_int), nodes_for_plot)
Chebyshev_int_values = interpolate(nodes_for_Chebyshev_int, fun(nodes_for_Chebyshev_int), nodes_for_plot)

import matplotlib.pyplot as plt

fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(nodes_for_plot, fun(nodes_for_plot))
axs[0, 0].plot(nodes_for_plot, uniform_int_values[:, 0])
axs[0, 0].plot(nodes_for_uniform_int, fun(nodes_for_uniform_int), marker = '.', linestyle='none')
axs[0, 0].set_title('f(uniform)')
axs[0, 1].plot(nodes_for_plot, fun(nodes_for_plot))
axs[0, 1].plot(nodes_for_plot, Chebyshev_int_values[:, 0])
axs[0, 1].plot(nodes_for_Chebyshev_int, fun(nodes_for_Chebyshev_int), marker = '.', linestyle='none')
axs[0, 1].set_title('f(Chebyshev)')
axs[1, 0].plot(nodes_for_plot, der(nodes_for_plot))
axs[1, 0].plot(nodes_for_plot, uniform_int_values[:, 1])
axs[1, 0].plot(nodes_for_uniform_int, der(nodes_for_uniform_int), marker = '.', linestyle='none')
axs[1, 0].set_title('d(uniform)')
axs[1, 1].plot(nodes_for_plot, der(nodes_for_plot))
axs[1, 1].plot(nodes_for_plot, Chebyshev_int_values[:, 1])
axs[1, 1].plot(nodes_for_Chebyshev_int, der(nodes_for_Chebyshev_int), marker = '.', linestyle='none')
axs[1, 1].set_title('d(Chebyshev)')

plt.show()
