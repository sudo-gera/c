

from urllib.request import Request as request
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
from requests import post
from random import randint
from random import choice

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

q=api('photos.getWallUploadServer?group_id=186041959')['response']
print(q)
#d=urlopen('http://192.168.43.1:9000',data='--d4cae89ef506420b88e5c9e1b8f91f28\r\nContent-Disposition: form-data; name="photo"; filename="boot.jpg"\r\n\r\n'.encode()+open('/boot.jpg','rb').read()+'\n\r\n--d4cae89ef506420b88e5c9e1b8f91f28--\r\n'.encode()).read()
ph=open('/boot.jpg','rb').read()
rs=''
while rs.encode() in ph:
 rs=''.join([choice('1234567890poiuytrewqasdfghjklmnbvcxzQWERTYUIOPLKJHGFDSAZXCVBNM') for w in range(32)])
data=('--'+rs+'\r\n'+'Content-Disposition: form-data; name=photo; filename=mem.jpg\r\nContent-Type: image/jpeg\r\n\r\n').encode()+ph+('--'+rs+'--').encode()
ad=q['upload_url']
ad=
d=urlopen(request(ad,data=data,headers={'Content-type':'multipart/form-data; boundary='+rs})).read()
#d=urlopen(q['upload_url'],data='--'.encode()+rs+'\r\nContent-Disposition: form-data; name="photo"; filename="boot.jpg"\r\n\r\n'.encode()+ph+'\r\n--'.encode()+rs+'--\r\n'.encode()).read()
#d=post(q['upload_url'],files=dict(photo=open('/boot.jpg','rb')))
#d=post('http://192.168.43.1:9000',files=dict(photo=open('exe.py','rb')))
#d=d.text
print(d)
#exit()
d=loads(d)
f=api('photos.saveWallPhoto?group_id=186041959&photo='+d['photo']+'&server='+str(d['server'])+'&hash='+d['hash'])
print(f)
a=api('wall.post?owner_id=-186041959&from_group=1&attachments=photo225847803_'+str(f['response'][0]['id']))
print(a)
