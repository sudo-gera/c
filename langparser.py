from sys import argv
from functools import reduce
from re import *
from keyword import kwlist
from pprint import pprint
def error(l,q):
	print('\x1b[31m[error line '+str(l)+']\x1b[0m',q)
	exit()
def lprint(q):
	print('lprint',q)
	return q
if len(argv)>1:
	filename=argv[1]
	text=open(filename).read()
else:
	from sys import stdin
	text=stdin.read()
strings=[
	['"""','"""'],
	["'''","'''"],
	['"','"'],
	["'","'"],
	['r"""','"""'],
	["r'''","'''"],
	['r"','"'],
	["r'","'"],
	['u"""','"""'],
	["u'''","'''"],
	['u"','"'],
	["u'","'"],
	['f"""','"""'],
	["f'''","'''"],
	['f"','"'],
	["f'","'"]
]
comments=[["#","\n"]]
# comments+=[["/*","*/"]]
specials=strings+comments
################
text_list=['']
started=''
while text:
	iteration=1
	if started:
		for symb in specials:
			if symb[0]==started and text.startswith(symb[1]):
				text_list[-1]+=symb[1]
				text_list.append('')
				started=''
				text=text[len(symb[1]):]
				iteration=0
				break
		if iteration:
			text_list[-1]+=text[0]
			text=text[1:]
	else:
		for symb in specials:
			if text.startswith(symb[0]):
				started=symb[0]
				text_list.append('')
				text_list[-1]+=symb[0]
				text=text[len(symb[0]):]
				iteration=0
				break
		if iteration:
			text_list[-1]+=text[0]
			text=text[1:]
#############
uniqstrings=dict()
_next_int=1234567890987654321
def next_int():
	global _next_int
	_next_int+=1
	return _next_int
def randomstring(s=None):
	r=''.join([''[int(w)] for w in str(next_int())])
	if s!=None:
		if s in uniqstrings:
			return uniqstrings[s]
		else:
			uniqstrings[s]=r
	return '_'*20+r
enter_count=1
def count_lines(w):
	global enter_count
	enter_count+=w.count('\n')+w.count('\r')
	return enter_count
text_list=[[1,w,count_lines(w)] for w in text_list]
for w in range(1,len(text_list)):
	text_list[w][0]=text_list[w-1][2]
text_list=[[bw,'string_generator('+','.join([str(ord(q)) for q in eval(w)])+')' if any([w.startswith(_w[0]) for _w in strings]) else '' if any([w.startswith(_w[0]) for _w in comments]) else w,ew] for bw,w,ew in text_list]
text_list=['"'+str(w[0])+'"'+w[1]+'"'+str(w[2])+'"' for w in text_list]
text=''.join(text_list)
#########################
specials=['%=', '&=', '*=', '+=', '-=', '/=', '<=', '>=', '|=', '~=', '**', '//', '<<', '==', '>>', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '@', '@=', '[', ']', '^', '{', '|', '}', '~', '>>=', '<<=']
specials.sort(key=len,reverse=1)
name_start='qwertyuioplkjhgfdsaszxcvbnm_QWERTYUIOPLKJHGFDSASZXCVBNM'
name_contain='qwertyuioplkjhgfdsaszxcvbnm_QWERTYUIOPLKJHGFDSASZXCVBNM1234567890'
spaces=['\t','\f',' ','\\\n']
enters=['\n','\r']
text_list=[]
cline=1
while text:
	goup=0

	for w in spaces:
		if text.startswith(w):
			text=text[len(w):]
			goup=1
			break
	if goup:
		continue

	for w in enters:
		if text.startswith(w):
			text=text[len(w):]
			sc=0
			while text and text[0] in spaces:
				sc+=1
				text=text[1:]
			if w=='\n':
				cline+=1
			text_list.append({'name':('\n'+' '*sc),'type':'oper','line':cline})
			goup=1
			break
	if goup:
		continue

	a=match(r'^[qwertyuioplkjhgfdsaszxcvbnm_QWERTYUIOPLKJHGFDSASZXCVBNM][qwertyuioplkjhgfdsaszxcvbnm_QWERTYUIOPLKJHGFDSASZXCVBNM1234567890]*',text)
	if a:
		name=(text[a.start():a.end()])
		text_list.append({'name':name,'type':('oper' if name in kwlist else 'name'),'line':cline})
		text=text[a.end():]
		continue

	a=match(r'^[1234567890]+',text)
	s=([s for s in [match(r'^[1234567890]*\.[1234567890]+',text),match(r'^[1234567890]+\.[1234567890]*',text)] if s]+[None])[0]
	if a and not s:
		text_list.append({'name':(text[a.start():a.end()]),'type':'value','line':cline})
		text=text[a.end():]
		continue

	a=([s for s in [match(r'^[1234567890]*\.[1234567890]+',text),match(r'^[1234567890]+\.[1234567890]*',text)] if s]+[None])[0]
	if a:
		text_list.append({'name':(text[a.start():a.end()]),'type':'value','line':cline})
		text=text[a.end():]
		continue

	for w in specials:
		if text.startswith(w):
			text=text[len(w):]
			text_list.append({'name':(w),'type':'oper','line':cline})
			goup=1
			break
	if goup:
		continue

	if text.startswith('"'):
		text=text[1:]
		cline=int(text[:text.index('"')])
		text=text[text.index('"'):]
		text=text[1:]
		continue
	if len(argv)==1:
		print()
	error(cline,'could not read character '+repr(text[0]))
text_list_before=text_list[:]
text_list_after=[]
cindent=0
while text_list_before:
	if len(text_list_before)>1 and text_list_before[0]['type']=='oper' and text_list_before[0]['name']=='not' and text_list_before[1]['type']=='oper' and text_list_before[1]['name']=='in':
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['name']='not_in'
		text_list_before=text_list_before[2:]
	elif len(text_list_before)>1 and text_list_before[0]['type']=='oper' and text_list_before[0]['name']=='is' and text_list_before[1]['type']=='oper' and text_list_before[1]['name']=='not':
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['name']='is_not'
		text_list_before=text_list_before[2:]
	elif text_list_before[0]['type']=='oper' and text_list_before[0]['name']=='True':
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['type']='value'
		text_list_before=text_list_before[1:]
	elif text_list_before[0]['type']=='oper' and text_list_before[0]['name']=='False':
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['type']='value'
		text_list_before=text_list_before[1:]
	elif text_list_before[0]['type']=='oper' and text_list_before[0]['name']=='None':
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['type']='value'
		text_list_before=text_list_before[1:]
	elif text_list_before[0]['type']=='oper' and text_list_before[0]['name'][0]=='\n':
		nindent=len(text_list_before[0]['name'])-1
		text_list_after.append(text_list_before[0])
		text_list_after[-1]['name']='\n'
		while nindent>cindent:
			cindent+=1
			text_list_after.append({'name':'begin','type':'oper','line':text_list_before[0]['line']})
		while nindent<cindent:
			cindent-=1
			text_list_after.append({'name':'end','type':'oper','line':text_list_before[0]['line']})
		text_list_before=text_list_before[1:]
	else:
		text_list_after.append(text_list_before[0])
		text_list_before=text_list_before[1:]
text_list=text_list_after[:]
############################
def handle_parentheses(a):
	s=[]
	while a:
		if a[0]['type']=='oper' and a[0]['name'] in ['(','[','{']:
			s.append({'type':'seq','name':a[0]['name'],'line':a[0]['line'],'cont':[]})
			a=a[1:]
			opened=[]
			if len(a)==0:
				error(s[-1]['line'],'unmatched '+str(s[-1]['name']))
			while opened==[] and not(a[0]['type']=='oper' and a[0]['name']=={'(':')','[':']','{':'}'}[s[-1]['name']]):
				if a[0]['type']=='oper' and a[0]['name']==s[-1]['name']:
					opened.append(a[0])
				if a[0]['type']=='oper' and a[0]['name']=={'(':')','[':']','{':'}'}[s[-1]['name']]:
					opened.pop()
				s[-1]['cont'].append(a[0])
				a=a[1:]
				if len(a)==0:
					error(s[-1]['line'],'unmatched '+str(s[-1]['name']))
			a=a[1:]
			s[-1]['cont']=handle_parentheses(s[-1]['cont'])
		elif a[0]['type']=='oper' and a[0]['name'] in [')',']','}']:
			error(a[0]['line'],'unmatched '+str(a[0]['name']))
		else:
			s.append(a[0])
			a=a[1:]
	return s
def handle_calls(a):
	s=[]
	while a:
		if len(a)>1 and a[0]['type']!='oper' and a[1]['type']=='seq' and a[1]['name'] in '[(':
			s.append({'type':'seq','name':{'(':'call','[':'getitem'}[a[1]['name']],'line':a[0]['line'],'cont':[]})
			if a[0]['type']=='seq':
				a[0]['cont']=handle_calls(a[0]['cont'])
			s[-1]['cont'].append(a[0])
			s[-1]['cont']+=handle_calls(a[1]['cont'])
			a=a[2:]
		else:
			if a[0]['type']=='seq':
				a[0]['cont']=handle_calls(a[0]['cont'])
			s.append(a[0])
			a=a[1:]
	return s
def handle_opers_l2r(a,_ops):
	ops=[operators[w] for w in _ops]
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi+1]['type']=='oper' and a[wi+0]['type']!='oper' and\
				[w for w in ops if w['type']=='binary' and w['sign']==a[wi+1]['name']] and a[wi+2]['type']!='oper':
			s=a[wi:wi+3]
			a=a[:wi]+[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi+1]['name']][0]['name'],'line':a[wi+1]['line'],'cont':[]}]+a[wi+3:]
			if s[-3]['type']=='seq':
				s[-3]['cont']=handle_opers_l2r(s[-3]['cont'],_ops)
			a[wi]['cont'].append(s[-3])
			if s[-1]['type']=='seq':
				s[-1]['cont']=handle_opers_l2r(s[-1]['cont'],_ops)
			a[wi]['cont'].append(s[-1])
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_opers_l2r(a[wi]['cont'],_ops)
			wi+=1
	return a
def handle_opers_r2l(a,_ops):
	ops=[operators[w] for w in _ops]
	wi=len(a)
	while wi>0:
		if wi>1 and a[wi-2]['type']=='oper' and a[wi-1]['type']!='oper' and (\
				[w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']] and           a[wi-3]['type']!='oper'  or\
				[w for w in ops if w['type']=='unary'  and w['sign']==a[wi-2]['name']] and (wi==2 or a[wi-3]['type']=='oper') ):

			if  [w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']]:
				s=a[wi-3:wi]
				a=a[:wi-3]+[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]+a[wi:]
				wi-=2
				if s[-3]['type']=='seq':
					s[-3]['cont']=handle_opers_r2l(s[-3]['cont'],_ops)
				a[wi-1]['cont'].append(s[-3])
				if s[-1]['type']=='seq':
					s[-1]['cont']=handle_opers_r2l(s[-1]['cont'],_ops)
				a[wi-1]['cont'].append(s[-1])
			else:
				s=a[wi-2:wi]
				a=a[:wi-2]+[{'type':'seq','name':[w for w in ops if w['type']=='unary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]+a[wi:]
				wi-=1
				if s[-1]['type']=='seq':
					s[-1]['cont']=handle_opers_r2l(s[-1]['cont'],_ops)
				a[wi-1]['cont'].append(s[-1])
		else:
			if a[wi-1]['type']=='seq':
				a[wi-1]['cont']=handle_opers_r2l(a[wi-1]['cont'],_ops)
			wi-=1
	return a

text_list=handle_parentheses(text_list)
operators={'getattr': {'sign': '.', 'name': 'getattr', 'type': 'binary'}, 'pow': {'sign': '**', 'name': 'pow', 'type': 'binary'}, 'mul': {'sign': '*', 'name': 'mul', 'type': 'binary'}, 'matmul': {'sign': '@', 'name': 'matmul', 'type': 'binary'}, 'truediv': {'sign': '/', 'name': 'truediv', 'type': 'binary'}, 'floordiv': {'sign': '//', 'name': 'floordiv', 'type': 'binary'}, 'mod': {'sign': '%', 'name': 'mod', 'type': 'binary'}, 'add': {'sign': '+', 'name': 'add', 'type': 'binary'}, 'sub': {'sign': '-', 'name': 'sub', 'type': 'binary'}, 'lshift': {'sign': '<<', 'name': 'lshift', 'type': 'binary'}, 'rshift': {'sign': '>>', 'name': 'rshift', 'type': 'binary'}, 'and': {'sign': '&', 'name': 'and', 'type': 'binary'}, 'xor': {'sign': '^', 'name': 'xor', 'type': 'binary'}, 'or': {'sign': '|', 'name': 'or', 'type': 'binary'}, 'in': {'sign': 'in', 'name': 'contains', 'type': 'binary'}, 'not_in': {'sign': 'not_in', 'name': 'not_in', 'type': 'binary'}, 'is': {'sign': 'is', 'name': 'is', 'type': 'binary'}, 'is_not': {'sign': 'is_not', 'name': 'is_not', 'type': 'binary'}, 'lt': {'sign': '<', 'name': 'lt', 'type': 'binary'}, 'le': {'sign': '<=', 'name': 'le', 'type': 'binary'}, 'gt': {'sign': '>', 'name': 'gt', 'type': 'binary'}, 'ge': {'sign': '>=', 'name': 'ge', 'type': 'binary'}, 'ne': {'sign': '!=', 'name': 'ne', 'type': 'binary'}, 'eq': {'sign': '==', 'name': 'eq', 'type': 'binary'}, 'bool_and': {'sign': 'and', 'name': 'bool_and', 'type': 'binary'}, 'bool_or': {'sign': 'or', 'name': 'bool_or', 'type': 'binary'}, 'await': {'sign': 'await', 'name': 'await', 'type': 'unary'}, 'neg': {'sign': '-', 'name': 'neg', 'type': 'unary'}, 'pos': {'sign': '+', 'name': 'pos', 'type': 'unary'}, 'inv': {'sign': '~', 'name': 'inv', 'type': 'unary'}, 'not': {'sign': 'not', 'name': 'not', 'type': 'unary'}}
text_list=handle_opers_l2r(text_list,['getattr'])
text_list=handle_calls(text_list)
text_list=handle_opers_r2l(text_list,['await'])
text_list=handle_opers_r2l(text_list,['pow','await','neg','pos','inv'])
text_list=handle_opers_l2r(text_list,['mul','matmul','truediv','floordiv','mod'])
text_list=handle_opers_l2r(text_list,['add','sub'])
text_list=handle_opers_l2r(text_list,['lshift','rshift'])
text_list=handle_opers_l2r(text_list,['and'])
text_list=handle_opers_l2r(text_list,['xor'])
text_list=handle_opers_l2r(text_list,['or'])
text_list=handle_opers_l2r(text_list,['in','not_in','is','is_not','lt','le','gt','ge','ne','eq'])
text_list=handle_opers_r2l(text_list,['not'])
text_list=handle_opers_l2r(text_list,['bool_and'])
text_list=handle_opers_l2r(text_list,['bool_or'])
















if len(argv)==1:
	print()
from pprint import pprint
pprint(text_list)