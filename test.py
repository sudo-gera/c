def ack(n, m):
    for n in range(n, 0, -1):
        m = ack(n, m - 1) if m else 1
    return m + 1

for q in range(20):
    for w in range(20):
        try:
            a=ack(q,w)
        except RecursionError:
            a = -1
        print(f'{a:8d}',end='')
        import sys
        sys.stdout.flush()
    print()

