from h import *


from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote_plus
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from os import popen
from webbrowser import open as webopen
from sys import argv
from pathlib import Path
from pprint import pprint
import requests

token = open(home+'.photo_bot_token').read()

# url=open(str(Path.home())+'/url').read()
# token=url.split('#')[1].split('&')[0].split('=')[1]

class obj(dict): # allow a.name instead of a['name']
    def __init__(self,*a,**s):
        super().__init__(*a,**s)
        self.__dict__=self

def convert(a): # recursively replace dict with obj in json
    if type(a)==dict:
        return obj({q:convert(w) for q,w in a.items()})
    if type(a)==list:
        return [convert(q) for q in a]
    return a

def items(q):
    if type(q) == type(dict()):
        if set(q.keys()) == set(['count', 'items']):
            return items(q['items'])
        else:
            for w in q:
                q[w] = items(q[w])
            return q
    elif type(q) == type(list()):
        return [items(w) for w in q]
    else:
        return q

def api_f(path,data=''):
    if path and path[-1] not in '&?':
        if '?' in path:
            path+='&'
        else:
            path+='?'
    sleep(1/5)
    data=data.encode()
    global token
    ret=loads(urlopen('https://api.vk.com/method/'+path+'v=5.131&access_token='+token,data=data).read().decode())
    try:
        if 'error' in ret.keys():
            print(ret['error']['error_msg'])
    except:
        pprint(ret)
    try:
        return convert(items(ret['response']))
    except:
        pass


class Api:
    def __init__(self,s=''):
        self._s=s
    def __getattr__(self,n):
        return Api(self._s+'.'*(not not self._s)+n)
    def __call__(self,**d):
        s=self._s+'?'
        d=[w+'='+quote_plus(str(d[w])) for w in d]
        d='&'.join(d)
        return api_f(s+d)

api=Api()

def send_photo(photo,to):
    a=api.photos.getMessagesUploadServer(peer_id=to)
    a=requests.post(a.upload_url, files={'file': (photo.split('/')[-1], open(photo,'rb').read())}).json()
    a=api.photos.saveMessagesPhoto(**a)
    a=api.messages.send(user_id=to, random_id=0, attachment=f'''photo{a[0].owner_id}_{a[0].id}''')

def walk(path):
    for q in sorted(os.listdir(path),key=lambda q: os.path.getctime(path+'/'+q)):
        w=path+'/'+q
        if os.path.isdir(w):
            yield ['dir',w]
            yield from walk(w)
        else:
            yield ['file',w]

for q in walk('.'):
    print(q)


