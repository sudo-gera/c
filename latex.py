from sys import argv
from subprocess import run
a=run(['pdflatex',argv[1]],input=b'\n'*1024,capture_output=...)
s=a.returncode
a=a.stdout.decode()
a=a[(a+'\n!').index('\n!'):(a+'\n? !').index('\n? !')].strip()
if a:
	print(a)
exit(s)
