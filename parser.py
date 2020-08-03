from urllib.request import urlopen as u
q=u('http://kpml.ru/pages/raspisanie/izmeneniya-v-raspisanii').read().decode()
print(q)
'''
q=open('site').read()
q=q.split('\n')
q=[[len(w),w] for w in q]
q=max(q)[1]
q=q.replace('&nbsp;','')
q=q.replace('>','>\n')
q=q.replace('<','\n<')
q=q.replace('\n\n','\n')
q=q.split('\n')
q=[[w,'',''] for w in q if w and w[0] != '<']
i=''
for w in q:
 if w[0][:9] == 'Изменения':
  i=w[0].split('-')[1]
  i=i.lower()
  i=i.split()
  i[1]='января февраля марта апреля мая июня июля августа сентября октября ноября декабря'.split().index(i[1])
  i[1]+=1
  i=i[:-1]
 else:
  w[1]=i
for w in q:
 w[0]=w[0].strip()
c=[]
for w in 'АБВ':
 for e in range(1,12):
  c+=[str(e)+w]
e=''
for w in q:
 if w[0] in c:
  e=w[0]
 else:
  w[2]=e
q=[(w[:1]+w[1]+w[2:])[::-1] for w in q if w[1] and w[2]]

#q='\n'.join(q)
'''
