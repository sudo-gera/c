import numpy as np

X = np.array([
    [0,0],
    [1,0],
    [0,1],
    [1,1],
])

y = np.array([
    [0],
    [1],
    [1],
    [0],
])

def sigmoid(x):
    return 1/(1+np.exp(-x))

def dsigmoid(a):
    return a*(1-a)

W1 = np.arange(8).reshape((2, 4)) * 1.0
b1 = np.zeros((1, 4))

W2 = np.arange(4).reshape((4,1)) * 1.0
b2 = np.zeros((1, 1))

lr = 0.1

for epoch in range(50_000):
    h = sigmoid(X @ W1 + b1)
    o = sigmoid(h @ W2 + b2)

    d_o = (y - o) * dsigmoid(o)
    d_h = d_o @ W2.T * dsigmoid(h)

    W2 += lr * h.T @ d_o
    b2 += lr * np.sum(d_o, axis=0, keepdims=True)

    W1 += lr * X.T @ d_h
    b1 += lr * np.sum(d_h, axis=0, keepdims=True)

for x, p in zip(X, o):
    print(x.astype(int), "->", round(float(p[0]), 4))



