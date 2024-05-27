from h import *

def ft(n, b):
    return to_radix_list(n, b).count(4)

for n in range(2, 10000):
    print(max([
        [ft(n, b), n, b, n-b]
        for b in range(2, n+2)
    ]))
