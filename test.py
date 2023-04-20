from sys import *
n=2**16
if len(argv)>1:
    print(n-1)
    for w in range(n):
        print(9,end=' ')
    print()
    print(n-1)
    for w in range(n):
        print(-9,end=' ')
    print()
else:
    print(2*n-2,end=' ')
    for q in range(1,n):
        print(-q*9*9,end=' ')
    for q in range(n,0,-1):
        print(-q*9*9,end=' ')
print()
