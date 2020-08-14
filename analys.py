exec(open('/home/gera/.pythonrc').read())
q=open(argv[1]).read()
q=q.replace('<','\n<').replace('>','>\n').replace('\n\n','\n').replace('&nbsp;','').split('</tr>')
q=[w.split('</td>') for w in q]
q=[w for w in q if len(w)==7]
q=[w[-3] for w in q]
q=[''.join(' '.join([e for e in w.replace('<','\0<').replace('>','>\0').split('\0') if e and set([e[0],e[-1]]) & set('<>') == set()]).split()) for w in q]
q=[[sum([int(e)*2-7 if e in '0987654321' else 0 for e in w]),w] for w in q]
'''
q=[list(w) for w in q]
for w in range(len(q)):
 o=0
 for e in range(len(q[w])):
  c=0
  if q[w][e]=='<':
   o+=1
  if o:
   c=1
  if q[w][e]=='>':
   o-=1
  if c:
   q[w][e]=''
q=[''.join(w) for w in q]
q=[' '.join(w.split()) for w in q if w.split()]
q=[w for w in q if '(' not in w]
q=[''.join([e for e in w if e not in ' ']) for w in q]
q=[w for w in q if w]
q=[[sum([int(e)*2-7 if e in '1234567890' else 0 for e in w]),w] for w in q]
'''
q=[('                                            \x1b[30;47m'+str(w[1])+'\x1b[0m'+' '*(40-len(w[1])-max(0,-w[0]))+(' \x1b[41m' if w[0]<0 else ' \x1b[42m')+'-'*abs(w[0])+'\x1b[0m ').replace('------','---===').replace('-----','---==').replace('----','---=') for w in q]
#q=q[-37:]
#q[5]=''
'''
q=[w for w in q if w]
c=0
for w in range(len(q)):
 if c:
  pass
 else:
  q[w]=''
  pass
 c=1-c
'''
#print(*['\n-------------\n'.join(w) for w in q],sep='\n----------------------------------\n')
print(*[(w) for w in q],sep='\n\n')

