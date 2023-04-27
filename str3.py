n=[None,None]
a=[None,None]
s=[None,None]
n[0]=int(input())
s[0]=[int(w) for w in input().split()]
a[0]=[int(w) for w in input().split()]
n[1]=int(input())
s[1]=[int(w) for w in input().split()]
a[1]=[int(w) for w in input().split()]
o=[0,0]
p=[a[0][0],a[1][0]]
i=0
d=0
def sum_less_eq(n):
    return n*(n+1)//2
while 1:
    c=p.index(min(p))
    if s[0][o[0]]!=s[1][o[1]]:
        d+=sum_less_eq(i+p[c])
        d-=sum_less_eq(i)
    i+=p[c]
    p[not c]-=p[c]
    p[c]-=p[c]
    assert (p[0]==0 and o[0]+1==len(a[0])) == (p[1]==0 and o[1]+1==len(a[1]))
    if p[0]==0 and o[0]+1==len(a[0]):
        break
    if p[0]==0:
        o[0]+=1
        p[0]=a[0][o[0]]
    if p[1]==0:
        o[1]+=1
        p[1]=a[1][o[1]]
print(d)        


