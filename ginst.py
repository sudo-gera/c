#!/usr/bin/python3
from sys import argv
from subprocess import run
import os
if not os.geteuid() == 0:
	run(['sudo','python3',__file__])
	exit()
	
