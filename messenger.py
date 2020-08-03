

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from os import popen

token="099413bc13d6bccbca6a2fd13447b4bb09e36e385a7571465c1464b7bed3072bef6be9a3a1818a57191e5"

def jprint(q):
 q=str(q)
 o=0
 b='{['
 e='}]'
 s=''
 n=''
 for w in q:
  if w in e:
   o-=1
   s=s[:-1]
   n+='\n'+o*' '
  if w in b:
   n+='\n'+o*' '
  n+=w
  if w in b:
   s+=w
   o+=1
   n+='\n'+' '*o
  if w in e+',':
   n+='\n'+' '*o
 n=n.split('\n')
 n=[w for w in n if w != ' '*len(w)]
 n='\n'.join(n)
 print(n)


def api(path,data):
 sleep(1/10)
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 return ret

def look(a=0):
 q=api('messages.getConversations?count=2&','')
 if 'response' not in q.keys():
   pass
 q=q['response']['items']
 return q
 q=[[w['conversation']['peer']['id'],w['last_message']['text'],w] for w in q if w['conversation']['can_write']['allowed']]
 if a==0:
  q=[w[:2] for w in q]
 q=[[str(w[0])]+w[1:] for w in q]
 q=[[w[0],w[1].lower(),w[1]] for w in q]
 return q

def read(id,off):
 q=api('messages.getHistory?offset='+str(off)+'&count=2&user_id='+str(id)+'&peer_id='+str(id)+'&start_message_id=-1')
 q=q['response']
 return q

def send(text,key='',id=None):
  text=str(text)
  global q
  if id==None:
   id=q[0]
  global d
  global defkey
  if key=='':
   key=defkey[:]
  while len(text)>4096:
   send(text[:4096],key,id)
   text=text[4096:]
  if key==defkey:
   if db[id]['empty']:
    key+='g×включить пустые сообщения'
   else:
    key+='r×отключить пустые сообщения'
  key='{"buttons":['+','.join(['['+','.join(['{"color":"'+d[e.split('×')[0]]+'","action":{"type":"text","label":"'+e.split('×')[1]+'"}}' for e in w.split('|')]) +']' for w in key.split('\n') if w])+']}'
  key='&keyboard='+key
  text=str(text)
  qq=api('messages.send?random_id='+str(time()).replace('.','')+'&user_id='+str(id)+'&','message='+text+key)
  print(qq)
  r=1
  if list(qq.keys())!=['response']:
   try:
    if qq['error']['error_code'] in [901,10,5]:
     r=0
   except:
    pass
   if r:
    log(qq)

jprint(look())
