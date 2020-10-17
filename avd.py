

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


q=api('video.search','q=&count=200&sort=0')['response']['items']
ban='|_/'
for w in q:
 for e in ban:
  w['title']=w['title'].replace(e,'_')
for w in q:

# print('#'+w['title'])
 print('wget '+w['files'][list(w['files'].keys())[-1]]+' -O '+w['title']+'.mp4')

#q=[w['title']+'\n'+w['files'][list(w['files'].keys())[-1]] for w in q]
#print(*q,sep='\n\n')
