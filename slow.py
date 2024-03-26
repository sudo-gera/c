
from iceream import ic

n = int(input())
a = [*map(int, input().split())]


def solve(state: int):
    ic(bin(state))
    f = float('-inf')
    if state == 2**len(a)-1:
        return 9
    for q in range(len(a)):
        if state & (1<<q) == 0:
            for w in range(len(a)):
                if state & (1<<w) == 0 and q != w:
                    ic(state | (1<<q) | (1<<w))
                    f = max(f, solve(state | (1<<q) | (1<<w)))
    return f

print(solve(0))
    
    

