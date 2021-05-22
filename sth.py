n=int(input())
q=[list(map(int,input().split())) for w in range(n)]
a=[[(w[0]+e[0],w[1]+e[1]),[w,e]] for w in q for e in q]
s={}
for w in a:
	s[w[0]]=[]
for w in a:
	s[w[0]].append(w[1])
