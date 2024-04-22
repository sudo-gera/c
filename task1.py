import matplotlib.pyplot as plt
import numpy as np

power=9
center=2
coef = [*map(round, (np.polynomial.Polynomial([-center, 1])**power).coef)] # coef[i] * x**i

meps = 1/2**53

def horner(coef, x):
    res = 0
    for c in coef[::-1]:
        res *= x
        res += c
    return res

xs = np.linspace(center-0.08, center+0.08, 1000)

def err(coef, x):
    n = len(coef)-1
    res = abs(coef[n] * x**n * (2*n-1))
    for i in range(0, n):
        res += abs(coef[i] * x**i * (2*i))
    return res*meps

horner_ys = [float(horner(coef, x)) for x in xs]
exact_ys = [(x-center)**power for x in xs]
error_ys = [err(coef, x) for x in xs]
min_ys = [y-e for y,e in zip(exact_ys, error_ys)]
max_ys = [y+e for y,e in zip(exact_ys, error_ys)]

plt.figure()
plt.plot(xs,horner_ys)
plt.plot(xs,exact_ys)
plt.plot(xs,min_ys)
plt.plot(xs,max_ys)
plt.show()



