#!/usr/bin/python3
from sys import argv
from subprocess import run
ex=argv[0]
argv=argv[1:]
if all([w.startswith('-') for w in argv]):
	file='-'
else:
	file=[w for w in argv if not w.startswith('-')][0]
ca=argv[:argv.index(file)+1]
ra=argv[argv.index(file)+1:]
ca='g++ -g -fsanitize=address,undefined -std=c++17 -Wfatal-errors'.split()+ca
ra='gdb ./a.out'.split()+ra
if run(ca).returncode:
	exit()
a=run(ra).returncode
if a:
	print(f'proxess stopped with exit code {a}')

