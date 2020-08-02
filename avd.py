

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from os import popen
from os import system
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


def com(a):
 q=list(a['title'])
 for e in range(len(q)):
  if not q[e].isdigit():
   q[e]='-'
 q=''.join(q).split('-')
 q=[int(w) for w in q if w]
 return q+[-a['duration'],0,0,0,0,0,0,0]
skey=argv[1]
file=argv[2]
q=api('video.search','q='+skey+'&count=200&sort=0&adult=1&filters=mp4&longer=300')['response']['items']
ban='|/ ()\t\n'
q.sort(key=com)
c=0
ext=[]
for w in q:
 c+=1
 t=w['title']
 for e in ban:
  t=t.replace(e,'_')
 f=w['files']
 d=w['duration']
 while list(f.keys()) and (f[list(f.keys())[-1]][:28]!='https://pvv4.vkuservideo.net' or 'mp4_' not in list(f.keys())[-1]):
  del(f[list(f.keys())[-1]])
# if not arg:
#  l=list(f.keys())
#  if not all(['mp4_' in w for w in l]):
#   print('\x1b[32m',l,'\x1b[0m')
 if list(f.keys()):
# if 1:
  ext+=[[c,d,t,f[list(f.keys())[-1]]]]


a=open(file,'w')
for w in ext:
 c,d,t,f=w
 a.write(str(c)+'\t'+str(d//3600)+':'+str(d%3600//60)+':'+str(d%60)+'\t'+t+'.mp4\n')
a.close()
system('nano '+file)
ch=[int(w.split()[0]) for w in open(file).read().split('\n') if w]
a=open(file,'w')
for w in ext:
 c,d,t,f=w
 if c in ch:
  a.write('wget '+f+' -O '+t+'.mp4\n')

