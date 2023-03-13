from h import *

for n in range(1,9):
    for m in range(1,n+1):
        for k in range(1,m+1):
            p=gcd(n,m)
            a=n//p
            b=m//p
            if min(
                ceil(n/m)*k,
                n,
                n+k-m,
                ceil(k/b)*(a-b)+k,
            )>ceil(n*k/m):
                print(n,m,k)