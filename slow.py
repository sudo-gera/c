n = int(input())
a = [*map(int, input().split())]


def solve(state: int):
    f = float('-inf')
    if state == 2**len(a)-1:
        return 0
    for q in range(len(a)):
        if state & (1<<q) == 0:
            for w in range(q):
                if state & (1<<w) == 0:
                    m = solve(state | (1<<q) | (1<<w))
                    f = max(f, int(f'{a[q]}{a[w]}') + m, int(f'{a[w]}{a[q]}') + m)
    return f

print(solve(0))
    
    

