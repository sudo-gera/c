

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
from sys import argv

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
 sleep(1/6)
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 return ret


q=api('groups.get')['response']['items']
for w in [q[228]]:
 print('https://vk.com/club'+str(w))
 print(api('groups.getById?group_ids='+str(w)))
 e=api('wall.get?count=1&owner_id='+str(w))
 if 'response' in e:
  e=e['response']['items']
  e=[[r['date']//3600//24,r['id']] for r in e]
  print(e)
