from random import randint
from os import system
from time import *
c=0
while 1:
	a=open('stdin','wb')
#	[a.write(chr(randint(0,255))) for w in range(randint(0,255))]
	a.write(bytes([randint(0,255) for w in range(randint(0,255))]))
	a.write(b'\n')
#	[a.write(chr(randint(0,255))) for w in range(randint(0,255))]
#	a.write('\n')
	a.close()
	if system('python3 mhw.py < stdin > stdout'):
		print([open('stdin','rb').read()])
		sleep(0.4)
	c+=1
	if c%1234==0:
		print(asctime(),c)