import sys

def wide_rec(f, last=True, level=1, b=1, e=2):
    if level == 0:
        assert b + 1 == e
        f(b-1)
    elif last:
        wide_rec(f, False, level-1, b, e)
        wide_rec(f, last, level+1, e, e*2)
    else:
        assert (b + e) % 2 == 0
        c = (b+e)//2
        wide_rec(f, last, level-1, b, c)
        wide_rec(f, last, level-1, c, e)

a = [0]

def call(n):
    assert a[0] == n
    a[0] += 1

for n in range(8, 60):
    a[0] = 0
    sys.setrecursionlimit(n)
    try:
        wide_rec(call)
    except RecursionError:
        pass
    print(n, bin(a[0]))


