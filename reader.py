#q=open('site').read()
from urllib.request import urlopen as u
q=u('http://kpml.ru/pages/raspisanie/izmeneniya-v-raspisanii').read().decode()
q=q.split('\n')
q=[[len(w),w] for w in q]
q=max(q)
q=q[1]
q=q.replace('<','\n<').replace('>','>\n').split('\n')
q=[w for w in q if w]
q='\n'.join(q)
q=q.split('<p')
day=''
q=[[w,''] for w in q if w]
for w in q:
 if 'Изменения' in w[0]:
  day=w[0]
  day=day.split('\n')
  day=[e for e in day if e[:1]!='<']
  day='<!--1-->'.join(day)
 else:
  w[1]=day
q=['\n<!--00000-->\n'.join(w[::-1]) for w in q if w[1]]
q='<!--00000000000000000000000000000-->\n <p'.join(q)
open('csite.html','w').write(q)
