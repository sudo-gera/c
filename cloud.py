

from urllib.request import urlopen
from json import loads
from json import dumps
from urllib.parse import quote
from time import sleep
from time import time
from time import asctime
from traceback import format_exc as fo
from requests import post
_____op=open
exec('from os import *')
exec('from os.path import *')
open=_____op
from sys import argv
def api(path,data=''):
 if path and path[-1] not in '&?':
  if '?' in path:
   path+='&'
  else:
   path+='?'
 sleep(1/6)
 data=data.encode()
 global token
 ret=loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 try:
  return ret['response']
 except:
  print(ret)

def log(p=None):
	if p is None:
		print(' '*wid,end='\r')
	else:
		print('#'*int(p*wid),end='\r')

home=getenv('HOME')
if home[-1]!='/':
	home+='/'

if not exists(home+'.cloud.token'):
	group=dict()
	group['token']=input('''
select group or create one. You should be create of group.
allow messages to group and write a random to group from your account
create API token with acess to docs and messages and enter: ''')
	group['gid']=None
	group['cid']=None
	open(home+'.cloud.token','w').write(dumps(group))
group=loads(open(home+'.cloud.token').read())
token=group['token']
gid=group['gid']
cid=group['cid']

wid=get_terminal_size()[0]
if cid==None and gid==None:
	mes=api('messages.getConversations')['items']
	while mes==[]:
		print('send a random message to group from your account')
		mes=api('messages.getConversations')['items']
	mes=[w['conversation']['peer']['id'] for w in mes]
	mes=[[w] for w in mes]
	for w in mes:
		w[0]=api(f'docs.getMessagesUploadServer?peer_id={w[0]}')['upload_url']
		log(w.index(mes)/len(w))
	log()
	mes=[w for w in mes if w]
	mes=[w.split('?',1)[1].split('&') for w in mes]
	mes=[[e.split('=') for e in w] for w in mes]
	mes=[dict(w) for w in mes]
	d=dict()
	for e in mes[0].keys():
		if all([e in w and w[e]==mes[0][e] for w in mes]):
			d[e]=mes[0][e]
	for w in list(d.keys()):
		try:
			int(d[w])
		except:
			del(d[w])
	d=[d[w] for w in d if'id' in w and d[w][0]=='-']
	d=max(d,key=len)
	gid=str(abs(int(d)))
	mem=api(f'groups.getMembers?group_id={gid}&filter=managers')['items']
	mem=[w['id'] for w in mem if w['role']=='creator']
	cid=mem[0]
	group['gid']=gid
	group['cid']=cid
	open(home+'.cloud.token','w').write(dumps(group))

def post_data(data):
	name=str(time())+'.txt'
	open(home+'.cloud.tmp','wb').write(data)
	url=api(f'docs.getMessagesUploadServer?peer_id={cid}')['upload_url']
	r=post(url,files={'file':(name,open(home+'.cloud.tmp','rb'))}).json()
	url=api('docs.save?file='+r['file']+'&title='+name)['doc']['url']
	return url

def load_data(link):
	return urlopen(link).read()

class textfile:
	def __init__(self,text=''):
		self.data=bytearray(text.encode())
	def size(self):
		return len(self.data)
	def read(self,n=None):
		if n is None:
			f=self.data
			self.data=bytearray()
			return f
		else:
			f=self.data[:n]
			self.data=self.data[n:]
			return f
	def write(self,data):
		self.data+=bytearray(data)

def upload_file(file,size):
	a=''
	msize=200000000
	osize=size
	while size>msize:
		a+=post_data(file.read(200))+' '
		size-=msize
		log((osize-size)/osize)
	if size:
		a+=post_data(file.read())+' '
	log()
	a=a[:-1]
	return post_data(a.encode())

def download_file(file,link):
	a=load_data(link).decode().split()
	for w in a:
		file.write(load_data(w))
		log(a.index(w)/len(a))
	log()
	return file

if exists(home+'.cloud.link'):
	db=loads(download_file(textfile(),open(home+'.cloud.link').read()).read().decode())
else:
	db=dict()

if len(argv)<2:
	print(f'''
usage: {argv[0]} upload FILE
       {argv[0]} download FILE
       {argv[0]} list
''')
	exit()

if argv[1]=='upload':
	if len(argv)<3:
		print('usage: '+argv[0]+' upload FILE')
		exit()
	if not exists(argv[2]):
		print('file '+argv[2]+' not exists in local filesystem')
		exit()
	if argv[2] in db.keys():
		print('name '+argv[2]+' is already used in remote filesystem')
		exit()
	db[argv[2]]=upload_file(open(argv[2],'rb'),getsize(argv[2]))

if argv[1]=='download':
	if len(argv)<3:
		print('usage: '+argv[0]+' download FILE')
		exit()
	if exists(argv[2]):
		print('name '+argv[2]+' is already used in local filesystem')
		exit()
	if argv[2] not in db.keys():
		print('file '+argv[2]+' not exists in remote filesystem')
		exit()
	download_file(open(argv[2],'wb'),db[argv[2]])

if argv[1]=='list':
	for w in db.keys():
		print(w)
	exit()

db=textfile(dumps(db))
open(home+'.cloud.link','w').write(upload_file(db,db.size()))