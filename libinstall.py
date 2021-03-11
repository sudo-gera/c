from sys import argv
from subprocess import *
from os.path import *
from shutil import *
s=run(['find','/System/Volumes/Data/opt/homebrew/Cellar/','-name',argv[1]],capture_output=True).stdout.decode().strip()
if not exists('/Library/Developer/CommandLineTools/usr/include/c++/v1/'+argv[1]):
	copy(s,'/Library/Developer/CommandLineTools/usr/include/c++/v1/'+argv[1])
