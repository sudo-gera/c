import numpy as np
from scipy.special import roots_jacobi

def f(x):
    return np.exp(-1/x)*(np.sin(1/x))

def weight(x):
    return x

def gauss_kristoffel(n):
    nodes, weights = roots_jacobi(n, alpha=0, beta=0) 
    integral = 0
    for i in range(n):
        integral += weights[i] * f(nodes[i]) * weight(nodes[i])
    return integral

# Вычисляем интеграл с заданной погрешностью
n = 10
integral_prev = 0
integral_curr = gauss_kristoffel(n)
while abs(integral_curr - integral_prev) > 1e-6:
    integral_prev = integral_curr
    n += 1
    integral_curr = gauss_kristoffel(n)

print("Integral value:", integral_curr)
