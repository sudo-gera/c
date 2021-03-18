from sys import argv
from functools import reduce
#filename=argv[1]
#text=open(filename).read()
text=input()
specials=[
	['"','"'],
	["'","'"],
	["/*","*/"],
	["#","\n"]]
################
textl=['']
started=''
while text:
	iteration=1
	if started:
		for symb in specials:
			if symb[0]==started and text.startswith(symb[1]):
				textl[-1]+=symb[1]
				textl.append('')
				started=''
				text=text[len(symb[1]):]
				iteration=0
		if iteration:
			textl[-1]+=text[0]
			text=text[1:]
	else:
		for symb in specials:
			if text.startswith(symb[0]):
				started=symb[0]
				textl.append('')
				textl[-1]+=symb[0]
				text=text[len(symb[0]):]
				iteration=0
		if iteration:
			textl[-1]+=text[0]
			text=text[1:]
#strings=[string for string in textl if string and [symb for symb in ['""',"''"] if string.startswith(symb[0]) and string.endswith(symb[-1])]]
#############
uniqstrings=[]
_next_int=1234567890987654321
def next_int():
	global _next_int
	_next_int+=1
	return _next_int
def randomstring(s=None):
	r=''.join(['qwertyuioplkjhgfdsaszxcvbnm'[int(w)] for w in str(next_int())])
	if s!=None:
		if s in uniqstrings:
			return uniqstrings[s]
		else:
			uniqstrings[s]=r
	return r
strings=''
for tf in range(len(ftext)):
	