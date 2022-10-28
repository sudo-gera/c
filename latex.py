from sys import argv
from subprocess import run
from icecream import ic
# a=open(argv[1]).read()
# s=''
# d=0
# while a:
# 	if a[0]=='$':
# 		d=1-d
# 		s+=a[0]
# 		a=a[1:]
# 	elif a[0]=='_' and not d:
# 		s+='$_'
# 		a=a[1:]
# 		if a[0]=='{':
# 			b=1
# 			o=0
# 			while not(a[b]=='}' and a[b-1]!='\\' and o==0):
# 				if a[b]=='{':
# 					o+=1
# 				if a[b]=='}':
# 					o-=1
# 				b+=1;
# 			b+=1;
# 			s+=a[:b]+'$'
# 			a=a[b:]
# 		else:
# 			s+=a[0]+'$'
# 			a=a[1:]
# 	elif a[0]=='^' and not d:
# 		# ic(s,a)
# 		_s='$^'
# 		a=a[1:]
# 		if a[0]=='{':
# 			b=1
# 			o=0
# 			while not(a[b]=='}' and a[b-1]!='\\' and o==0):
# 				if a[b]=='{' and a[b-1]!='\\':
# 					o+=1
# 				if a[b]=='}' and a[b+1]!='\\':
# 					o-=1
# 				b+=1;
# 			b+=1;
# 		else:
# 			b=1
# 		if _s:
# 			s+=_s+a[:b]+'$'
# 			a=a[b:]
# 	elif a.startswith('% '):
# 		a=a[(a+'\n').index('\n'):]
# 	else:
# 		s+=a[0]
# 		a=a[1:]
# a=s.replace('$$','')
# open(argv[1]+'.tmp.tex','w').write(a)
# a=run(['pdflatex',argv[1]+'.tmp.tex'],input=b'\n'*1024,capture_output=...)
# run(['cp',argv[1]+'.tmp.pdf',argv[1][:-3]+'pdf'])
# s=a.returncode
# a=a.stdout
# a=a[(a+b'\n!').index(b'\n!'):(a+b'\n?').index(b'\n?')].strip()
# if a:
# 	from sys import stdout
# 	stdout.buffer.write(a+b'\n')
# exit(s)
a=run(['xelatex',argv[1]])
