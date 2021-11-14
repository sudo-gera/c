from sys import argv
from subprocess import run
a=run(['pdflatex',argv[1]],input=b'\n'*1024,capture_output=...)
s=a.returncode
a=a.stdout
a=a[(a+b'\n!').index(b'\n!'):(a+b'\n?').index(b'\n?')].strip()
if a:
	from sys import stdout
	stdout.buffer.write(a+b'\n')
exit(s)
