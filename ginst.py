#!/usr/bin/python3
from sys import argv
from subprocess import run
from urllib.request import urlopen
import os
if not os.geteuid() == 0:
	run(['sudo','python3',__file__])
	from pathlib import Path
	open(str(Path.home())+'/g','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/g.py').read())
	open(str(Path.home())+'/v','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/v.py').read())
	open(str(Path.home())+'/b','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/b.py').read())

open('/usr/bin/wind','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/wind/master/wind.py').read())
open('/usr/bin/subl','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/subl').read())
