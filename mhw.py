from re import *
q=open('goto.in').read().lower()
q=list(q)
for w in range(len(q)-1):
	if q[w]=="'" and q[w+1]!="'":
		q[w]='_'
		q[w+1]="'"
	if q[w]=="'" and q[w+1]=="'":
		q[w]='_'
		q[w+1]='_'
	if q[w]=='{' and q[w+1]!='}':
		q[w]='_'
		q[w+1]='{'
	if q[w]=='{' and q[w+1]=='}':
		q[w]='_'
		q[w+1]='_'
q=''.join(q)
q=' '+q+' '
q=q.replace('#','_')
while findall(r'[\s\;\:\}]goto[\s\{]',q):
	q=sub(r'[\s\;\:\}]goto[\s\{]',r' # ',q)
print(q.count('#'),file=open('goto.out','w'))
