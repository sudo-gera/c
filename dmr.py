

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from os import popen


url=open('url').read()
token=url.split('=')[1].split('&')[0]
def api(path,data=''):
 sleep(1/10)
 if path and path[-1] not in '?&':
  if '?' in path:
   path+='&'
  else:
   path+='?'
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 if 'response' in ret:
  return ret['response']
 else:
  print(ret)

q=api('messages.getConversations?count=1')
q=q['items']
q=q[0]
id=q['conversation']['last_message_id']
q=api('messages.getById?message_ids='+','.join([str(w) for w in range(id,id-78,-1)]))
q=q['items']
e=api('users.get?user_ids='+','.join([str(w['from_id']) for w in q]+[str(w['peer_id']) for w in q]))
e=['"'+str(w['id'])+'":"'+w['first_name']+' '+w['last_name']+'"' for w in e]
e=','.join(e)
e='{'+e+'}'
e=loads(e)
def de(q):
 q=str(q)
 if q in e:
  return e[q]
 else:
  return q
q=['id: '+str(w['id'])+' time: '+str(w['date']%86400//3600+3)+':'+str(w['date']%3600//60)+':'+str(w['date']%60)+' from: '+de(w['from_id'])+(' ' if 'deleted' not in w else ' \x1b[31mdeleted\x1b[0m: ')+'\ntext: '+w['text']+('\n'+str(w))*0  for w in q]
q='\n\n'.join(q)
print(q)
q=input()
api('messages.restore?message_id='+q)
