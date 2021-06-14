from pprint import pprint
n=int(input())
q=[list(map(int,input().split())) for w in range(n)]
a=[[(w[0]+e[0],w[1]+e[1],(w[0]-e[0])**2+(w[1]-e[1])**2),[w,e]] for w in q for e in q]
s={}
for w in a:
	s[w[0]]=[]
for w in a:
	s[w[0]].append(w[1])
def cp(axb,axe,ayb,aye,bxb,bxe,byb,bye):
	ax=axe-axb
	ay=aye-ayb
	bx=bxe-bxb
	by=bye-byb
	return ax*by-bx*ay
d=[[abs(cp(w[0][0],e[0][0],w[0][1],e[0][1],w[0][0],e[1][0],w[0][1],e[1][1])),[w,e]] for q in s for w in s[q] for e in s[q]]
d.sort()
print(d[-1][0])