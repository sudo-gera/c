

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from os import popen
from webbrowser import open as webopen
#from sys import argv
argv=['j']

#print('a page will be opened. authorize and after it copy the url here')
#sleep(1)
#if len(argv)==1:
# webopen('https://oauth.vk.com/authorize?client_id=2685278&scope=1073737727&redirect_uri=https://oauth.vk.com/blank.html&display=page&response_type=token&revoke=1')
#sleep(1)
#url=input('paste the url:')
url=open('url').read()
token=url.split('#')[1].split('&')[0].split('=')[1]

def api(path,data=''):
 if path and path[-1] not in '&?':
  if '?' in path:
   path+='&'
  else:
   path+='?'
 sleep(1/3)
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 return ret


q=api('groups.get')['response']['items']+api('groups.get?offset=1000')['response']['items']
#q=api('groups.get')['response']['items']
c=0
a=[]
y=len(q)
while q:
 a+=[q[:25]]
 q=q[25:]
for w in a:
 s=w[:]
 w=[str(e) for e in w]
 w='''}),API.wall.get({'owner_id':-'''.join(w)
 t=api('execute','''code=return[API.wall.get({'owner_id':-'''+w+'''})];''')
 print(t)
 if 'response' not in t:
  print(t,s)
 else:
  t=t['response']
 c+=1
 for e in t:
  d=e
  print(e)
  e=e['items']
  e+=[{'date':0}]
  e=max([r['date']//86400 for r in e])
  if time()//86400-e>500:
   print('https://vk.com/club'+str(s[t.index(d)])+'               ')
  print('#'*c+'-'*(len(a)-c),end='\r')
