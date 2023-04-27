n=int(input())
a=[int(input()) for w in range(n)]
s=a[:]
s.sort()
d={}
for q,w in enumerate(a):
    d[w]=[q]
for q,w in enumerate(s):
    d[w].append(q)
c=0
for [q,[w,e]] in d.items():
    if (w-e)%2:
        c+=1
print(c//2)


