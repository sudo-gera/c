#!/usr/bin/python3
subl="/mnt/c/Program Files/Sublime Text 3/sublime_text.exe"
wsubl="C:/Program Files/Sublime Text 3/sublime_text.exe"

from sys import argv
from subprocess import run
from urllib.request import urlopen
from os.path import *
import os
if not os.geteuid() == 0:
	from pathlib import Path
	open(str(Path.home())+'/g','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/g1.py').read())
	run(['chmod','777',str(Path.home())+'/g'])
	open(str(Path.home())+'/v','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/v1.py').read())
	run(['chmod','777',str(Path.home())+'/v'])
	open(str(Path.home())+'/b','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/b1.py').read())
	run(['chmod','777',str(Path.home())+'/b'])
	open(str(Path.home())+'/.bashrc','a').write('\nPATH="$PATH:~/.local/bin:~:."\n')

	run(['sudo','python3',__file__])

	run(['subl',dirname(abspath(__file__))])
	exit()
else:
	open('/usr/bin/wind','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/wind/master/wind.py').read())
	run(['chmod','777','/usr/bin/wind'])
	open('/usr/bin/subl','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/subl').read().replace(b'/mnt/c/Program Files/Sublime Text/subl.exe',subl.encode()))
	run(['chmod','777','/usr/bin/subl'])
