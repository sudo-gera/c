n=int(input())
s=input()
n=len(s)

a=[]
for w in range(1,n+1):
    for q in range(w):
        d=s[q:w]
        if set(d)==set('abcd'):
            a.append(w-q)
if a:
    print(min(a))
else:
    print(-1)

