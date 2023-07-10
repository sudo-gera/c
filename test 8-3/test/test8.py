def read_set(n):
    if n<0:
        print('error')
        exit()
    return {
        int(input())
        for q in range(n)
    }
def print_set(s):
    print(len(s))
    print(*sorted(list(s)))
n,m=list(map(int,input().split()))
a=read_set(n)
s=read_set(m)
print_set(a&s)
print_set(a-s)
print_set(s-a)

