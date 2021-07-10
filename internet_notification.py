from os import system as s
from urllib.request import urlopen as u
from time import *
while 1:
	d=0
	t=time()
	while 1:
		try:
			u('https://vk.com',timeout=3600).read()
			break
		except:
			pass
	t=time()-t
	n=16/(max(d-t,0)+1)
	sleep(n)
	s('termux-notification -c '+str(t))
	d=d*.9+t*.1
