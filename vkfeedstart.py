''':'
if [ python $0 $@ -ne 0 ]
then
exit 1
fi
exit
':'''
from urllib.request import urlopen
from os import system
try:
 urlopen('http://127.0.0.1:9876').read()
except:
 system('vkfeed nocachegen')
 exit(1)
