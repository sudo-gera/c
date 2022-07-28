n,k=[int(w) for w in input().split()]
print(*sorted([int(input()) for w in range(n)],reverse=1)[:k],sep='\n')
