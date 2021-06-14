from sys import argv
from os.path import *
o=open
from os import *
open=o
from json import *
from re import *
from traceback import format_exc
from functools import *
make=loads(popen('python3 -c "from sys import argv\nfrom json import dumps\nprint(dumps(argv))" '+popen('make -n').read()).read())
libdir=[w[2:] for w in make if w.startswith('-I')]
ofiles=[w for w in make if w.endswith('.cpp') or w.endswith('.c') or w.endswith('.hpp') or w.endswith('.h')]
input(ofiles[0])
ef=ofiles[0]
file='\n'.join([open(w).read() for w in ofiles[::-1]])
@lru_cache(maxsize=None)
def namebyinclude(s,q,t=None):
	if t==None:
		t=q
	hs=findall(r'\s*#\s*include\s*'+q+r'(\s*.+)'+t+r'\s*',s)[0]
	for w in ['']+libdir:
		for e in [w+hs,w+'/'+hs]:
			if exists(e):
				return [e,open(e).read()]
	return [s,s.replace('include','include/**/')]
while findall(r'\s*#\s*include\s*"\s*.+"\s*',file):
	s=[w for w in file.split('\n') if fullmatch(r'\s*#\s*include\s*"\s*.+"\s*',w)][0]
	b=file.index(s)
	e=b+len(s)
	print(' '*80,end='\r')
	print(s,end='\r')
	file=file[:b]+'\n'+'//begin: '+namebyinclude(s,'"','"')[0]+'/'*80+'\n'+namebyinclude(s,'"','"')[1]+'\n'+'//end: '+namebyinclude(s,'"','"')[0]+'/'*80+'\n'+file[e:]
'''
while findall(r'\s*#\s*include\s*<\s*.+>\s*',file):
	s=[w for w in file.split('\n') if fullmatch(r'\s*#\s*include\s*<\s*.+>\s*',w)][0]
	b=file.index(s)
	e=b+len(s)
	print(' '*80,end='\r')
	print(s,end='\r')
	file=file[:b]+'\n'+'//begin: '+namebyinclude(s,'<','>')[0]+'/'*80+'\n'+namebyinclude(s,'<','>')[1]+'\n'+'//end: '+namebyinclude(s,'<','>')[0]+'/'*80+'\n'+file[e:]
'''
open(ef,'w').write(file)


