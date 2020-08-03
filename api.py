

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as error
from os import popen
from random import shuffle

token=open('url').read()
token=token[token.index('token')+6:token.index('&')]

def api(path,data=''):
 sleep(1/3)
 if path and path[-1] not in '?&':
  if '?' in path:
   path+='&'
  else:
   path+='?'
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 return ret
