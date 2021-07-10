from urllib.request import urlopen
from os import system
try:
 urlopen('http://127.0.0.1:9876').read()
except:
 system('vkfeed nocachegen')
