def to_bin(x):
    l = []
    while x != 0:
        l.append(x % 2)
        x //= 2
    l = [0 for i in range(8 - len(l))] + l
    return l

def my_not(x):
    if x == 1:
        return 0
    return 1

cnt = 0
for i in range(2**8):
    l = to_bin(i)
    while sum(l) != 0:
        l[sum(l) - 1] = my_not(l[sum(l) - 1])
        cnt += 1
print(cnt / 2**8)
