subl="/mnt/c/Program Files/Sublime Text 3/sublime_text.exe"
wsubl="C:/Program Files/Sublime Text 3/sublime_text.exe"

#!/usr/bin/python3
from sys import argv
from subprocess import run
from urllib.request import urlopen
import os
if not os.geteuid() == 0:
	from pathlib import Path
	open(str(Path.home())+'/g','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/g.py').read())
	run(['chmod','777',str(Path.home())+'/g'])
	open(str(Path.home())+'/v','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/v.py').read())
	run(['chmod','777',str(Path.home())+'/v'])
	open(str(Path.home())+'/b','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/b.py').read())
	run(['chmod','777',str(Path.home())+'/b'])

	run(['sudo','python3',__file__])

	run([wsubl,diranme(abspath(__file__))])
	exit()
else:
	open('/usr/bin/wind','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/wind/master/wind.py').read())
	run(['chmod','777','/usr/bin/wind'])
	open('/usr/bin/subl','wb').write(urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/subl').read().replace('/mnt/c/Program Files/Sublime Text/subl.exe',subl))
	run(['chmod','777','/usr/bin/subl'])
