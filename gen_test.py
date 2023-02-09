import random

def gen_test(n):
    global f
    for i in range(n):
        print(random.randint(0, n), end = " ", file = f)

with open("test.txt", "w") as f:
    n =random.randint(0, 2 * (10 ** 5))
    print(n, file = f)
    gen_test(n)
    