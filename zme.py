d='''рядовой:vs
матрос:f
ефрейтор:vs|
старший матрос:f|
младший сержант:vs||
старшина 2 статьи:f||
сержант:vs|||
старшина 1 статьи:f|||
старший сержант:vs#
главный старшина:f#
старшина:vs|#
главнй корабельный старшина:f|#
прапорщик:**
мичман:**
старший прапорщик:***
старший мичман:***
младщий лейтенант:-*
лейтенант:-**
старший лейтенант:-***
капитан:-****
капитан лейтенант:-****
майор:--*
капитан 3 ранга:--*
подполковник:--**
капитан 2 ранга:--**
полковник:--***
капитан 1 ранга:--***
генерал майор:^*
контрадмирал:^*
генерал лейтенант:^**
вицеадмирал:^**
генерал полковник:^***
адмирал:^***
генерал армии:^****
адмирал флота:^****
маршал рф:^*%'''.replace('\n','",\n"').replace(':','":"')
d='{"'+d+'"}'
exec('d='+d)
for w in d:
 d[w]=sorted(d[w])
from random import choice as c
w=[]
while 1:
 s=c(list(d.keys()))
 if w:
  s=c([s,s,s,s,s,w[0]])
  if s==w[0]:
   w=w[1:]
 print(s)
 f=sorted(input())
 if f!=d[s]:
  w+=[s,s,s,s,s,s,s]
 while f!=d[s]:
  f=sorted(input())

