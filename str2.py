n=int(input())
a=[input().split() for w in range(n)]
z=[eval(w[1]+'1') for w in a]
a=[int(w[0]) for w in a]
s=[0]*(n+1)
for q in range(len(a)):
    s[q+1]=s[q]+a[q]
s=s[1:]
x=[w for q,w in enumerate(s) if z[q]<0]
if x:
    x=-1-max(x)
    print(x+s[-1])
else:
    print('inf')
