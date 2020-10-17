n,m=map(int,input().split())
for w in range(n):
 m-=int(input().split()[1])
print(max(m,0))
