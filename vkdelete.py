from os import system as sh
sh('termux-open-url "http://oauth.vk.com/authorize?client_id=7149030&redirect_uri=oauth.vk.com/blank.html&display=page&response_type=token&scope=134217727"')
q=input()
q=q.split('#code=')[-1]
token=q

#token='0aa8e3ce455d115df9'
from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime

def api(path,data):
 sleep(1/3)
 data=data.encode()
 global token
 return loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())

def look(a=0):
 q=api('messages.getConversations?count=200&filter=unread&','')
 q=q['response']['items']
 q=[[w['conversation']['peer']['id'],w['last_message']['text'],w] for w in q if w['conversation']['can_write']['allowed']]
 if a==0:
  q=[w[:2] for w in q]
 q=[[str(w[0])]+w[1:] for w in q]
 q=[[w[0],w[1].lower(),w[1]] for w in q]
 return q

def send(id,text=None):
  global q
  if text==None:
   id,text=q[0],id
  text=str(text)
  qq=api('messages.send?random_id='+str(int(time()*2**28))+'&user_id='+str(id)+'&','message='+text)
  if list(qq.keys())!=['response']:
   print(qq)

def look(a=0):
 q=api('messages.getConversations?count=200&filter=unread&','')
 print(q)
 q=q['response']['items']
 q=[[w['conversation']['peer']['id'],w['last_message']['text'],w] for w in q if w['conversation']['can_write']['allowed']]
 if a==0:
  q=[w[:2] for w in q]
 q=[[str(w[0])]+w[1:] for w in q]
 q=[[w[0],w[1].lower(),w[1]] for w in q]
 return q

look()
