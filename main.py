#from android.permissions import request_permissions, Permission, check_permissions
from functools import partial
from json import loads
from json import dumps
from io import BytesIO as io
from io import StringIO
from kivy.app import App
from kivy.lang import Builder
from urllib.parse import quote
from urllib.parse import unquote
from urllib.request import urlopen as ou
from plyer import *
from pprint import pprint
#from requests_toolbelt import MultipartEncoder
from time import sleep
from time import time
_____op = open
exec('from os import *')
exec('from os.path import *')
open = _____op
from kivy.clock import Clock
rename_=rename
for w in dir(Clock):
	if '_' not in [w[:1],w[-1:]]:
		exec(w+'=Clock.'+w)

class _kg:
	def __getattr__(s, n):
		for w in [ 'uix.','storage.','network.','']:
			try:
				exec('from kivy.' + w + n.lower() + ' import ' + n)
				return eval(n)
			except:
				pass

get = _kg()

def run(*a):
#	root.children[-1].text=root.children[-2].text
	stdo=StringIO()
	global print
	pr1=print
	def print(*q,**w):
		pr1(*q,**w,file=stdo)
	try:
		exec(root.children[-2].text)
	except:
		print('an exception occured')
	print=pr1
	stdo.seek(0)
	root.children[-1].text=stdo.read()
	



class vk_cloud(App):
	def build(self):
		global root
		root=get.BoxLayout(orientation='vertical')
		root.add_widget(get.Label(text=''))
		root.add_widget(get.TextInput(multiline=True,on_text_validate=run))
		root.add_widget(get.Button(text='run',on_release=run))
		return root



vk_cloud().run()
