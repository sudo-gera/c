import sympy
def get_sum_polynom(n):
    n+=2
    d = sympy.Matrix([[
        w**q
        for q in range(n)[::-1]]
        for w in range(n*4)])
    a = d[:n, :].inv()
    s = sympy.Matrix([
        sum([w**(n-2)
        for w in range(q+1)])
        for q in range(len(d))])
    a = (a @ s[:n, :])
    for q,e in zip(*[map(m.row, range(m.rows)) for m in [s,d]]):
        assert (q - e@a)[0] == 0
    return list(a)
for n in range(0, 20):
    l=get_sum_polynom(n)
    print(f'{n}:', *l, sep='\t')

