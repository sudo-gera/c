input()
a=[('00000'+w)[-5:][::-1] for w in input().split()]
a.sort()
a=[w[::-1] for w in a]
a=[int(w) for w in a]
print(*a)
