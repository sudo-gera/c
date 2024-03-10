import itertools
import random

def combinations(a: list[int], k: int, s: int, d: list[int], res: list[list[int]]):
    if not len(a) >= k + s:
        return

    if k == 0:
        res.append(d[:])
        return
    if s == len(a)-1:
        d.append(a[s])
        res.append(d[:])
        d.pop()
        return
    
    d.append(a[s])
    combinations(a, k-1, s+1, d, res)
    d.pop()
    if len(a) != k + s:
        combinations(a, k, s+1, d, res)


for q in range(1000):
    for n in range(10):
        for k in range(n+1):
            a=[random.randint(0, n*2) for w in range(n)]
            # a=[w for w in range(n)]
            res1 : list[list[int]] = []
            combinations(a, k, 0, [], res1)
            res2 = [*itertools.combinations(a, k)]
            res3 = [tuple(w) for w in res1]
            if not res3 == res2:
                print(res1)
                print(res2)
                assert 0
                


