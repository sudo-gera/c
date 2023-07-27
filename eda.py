t = int(input())

def floor_2nd_root(n):
    begin=0
    end=n+1
    while begin+1!=end:
        center=(begin+end)//2
        if center**2 > n:
            end = center
        else:
            begin = center
    return begin

def floor_3rd_root(n):
    begin=0
    end=n+1
    while begin+1!=end:
        center=(begin+end)//2
        if center**3 > n:
            end = center
        else:
            begin = center
    return begin

for test in range(t):
    n = int(input())
    squares_or_cubes_count=0
    squares_or_cubes_count += floor_2nd_root(n)
    squares_or_cubes_count += floor_3rd_root(n)
    squares_or_cubes_count -= floor_2nd_root(floor_3rd_root(n))
    print(squares_or_cubes_count)
