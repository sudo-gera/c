n,k=[int(w) for w in input().split()]
if k==1:
    if n%2:
        for w in range(1,n+1,2):
            print(w,end=' ')
        for w in range(n-1,0,-2):
            print(w,end=' ')
    else:
        for w in range(1,n+1,2):
            print(w,end=' ')
        for w in range(n,0,-2):
            print(w,end=' ')
if k==2:
    if n%2:
        for w in range(2,n+1,2):
            print(w,end=' ')
        for w in range(n,0,-2):
            print(w,end=' ')
    else:
        for w in range(2,n+1,2):
            print(w,end=' ')
        for w in range(n-1,0,-2):
            print(w,end=' ')
if k==n-1:
    if n%2:
        for w in range(n-1,0,-2):
            print(w,end=' ')
        for w in range(1,n+1,2):
            print(w,end=' ')
    else:
        for w in range(n-1,0,-2):
            print(w,end=' ')
        for w in range(2,n+1,2):
            print(w,end=' ')
if k==n:
    if n%2:
        for w in range(n,0,-2):
            print(w,end=' ')
        for w in range(2,n+1,2):
            print(w,end=' ')
    else:
        for w in range(n,0,-2):
            print(w,end=' ')
        for w in range(1,n+1,2):
            print(w,end=' ')
print()