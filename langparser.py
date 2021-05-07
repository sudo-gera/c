from sys import argv
from functools import reduce
from re import *
from keyword import kwlist
from pprint import pprint
def error(l,q):
	print('\x1b[31m[error line '+str(l)+']\x1b[0m',q)
	exit(1)
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
	['R"""','"""'],
	["R'''","'''"],
	['R"','"'],
	["R'","'"],
	['U"""','"""'],
	["U'''","'''"],
	['U"','"'],
	["U'","'"],
	['f"""','"""'],
	["f'''","'''"],
	['f"','"'],
	["f'","'"],
	['F"""','"""'],
	["F'''","'''"],
	['F"','"'],
	["F'","'"],
]
comments=[["#","\n"]]
# comments+=[["/*","*/"]]
specials=strings+comments
################
text_list=['']
started=''
# f_string_open=''
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
				# if symb[1]=='{':
				# 	strings.append(['}','{'])
				# 	for w in strings:
				# 		if w[0]==f_string_open:
				# 			string.append(['}',w[1]])

				break
		if iteration:
			text_list[-1]+=text[0]
			text=text[1:]
	else:
		for symb in specials:
			if text.startswith(symb[0]):
				# if symb[0][0] in 'fF':
				# 	f_string_open=symb[1]
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
def string_generator(w):
	#todo f''
	return 'string_generator('+','.join([str(ord(q)) for q in eval(w)])+')'
text_list=[[bw,string_generator(w) if any([w.startswith(_w[0]) for _w in strings]) else '' if any([w.startswith(_w[0]) for _w in comments]) else w,ew] for bw,w,ew in text_list]
text_list=['"'+str(w[0])+'"'+w[1]+'"'+str(w[2])+'"' for w in text_list]
text=''.join(text_list)+'\n'
#########################
specials=['%=', '->', '&=', ':=', '*=', '+=', '-=', '/=', '<=', '>=', '|=', '~=', '**', '//', '<<', '==', '>>', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '@', '@=', '[', ']', '^', '{', '|', '}', '~', '>>=', '<<=', '!=']
operators={'getattr': {'sign': '.', 'name': 'getattr', 'type': 'binary'}, 'def_val': {'sign': '=', 'name': 'def_val', 'type': 'binary'}, 'd_unpack': {'sign': '**', 'name': 'd_unpack', 'type': 'unary'}, 'a_unpack': {'sign': '*', 'name': 'a_unpack', 'type': 'unary'}, 'expr_assign': {'sign': ':=', 'name': 'expr_assign', 'type': 'binary'}, 'assign': {'sign': '=', 'name': 'assign', 'type': 'binary'}, 'comma': {'sign': ',', 'name': 'comma', 'type': 'binary'}, 'pow': {'sign': '**', 'name': 'pow', 'type': 'binary'}, 'mul': {'sign': '*', 'name': 'mul', 'type': 'binary'}, 'matmul': {'sign': '@', 'name': 'matmul', 'type': 'binary'}, 'truediv': {'sign': '/', 'name': 'truediv', 'type': 'binary'}, 'floordiv': {'sign': '//', 'name': 'floordiv', 'type': 'binary'}, 'mod': {'sign': '%', 'name': 'mod', 'type': 'binary'}, 'add': {'sign': '+', 'name': 'add', 'type': 'binary'}, 'sub': {'sign': '-', 'name': 'sub', 'type': 'binary'}, 'lshift': {'sign': '<<', 'name': 'lshift', 'type': 'binary'}, 'rshift': {'sign': '>>', 'name': 'rshift', 'type': 'binary'}, 'ipow': {'sign': '**=', 'name': 'ipow', 'type': 'binary'}, 'imul': {'sign': '*=', 'name': 'imul', 'type': 'binary'}, 'imatmul': {'sign': '@=', 'name': 'imatmul', 'type': 'binary'}, 'itruediv': {'sign': '/=', 'name': 'itruediv', 'type': 'binary'}, 'ifloordiv': {'sign': '//=', 'name': 'ifloordiv', 'type': 'binary'}, 'imod': {'sign': '%=', 'name': 'imod', 'type': 'binary'}, 'iadd': {'sign': '+=', 'name': 'iadd', 'type': 'binary'}, 'isub': {'sign': '-=', 'name': 'isub', 'type': 'binary'}, 'ilshift': {'sign': '<<=', 'name': 'ilshift', 'type': 'binary'}, 'irshift': {'sign': '>>=', 'name': 'irshift', 'type': 'binary'}, 'and': {'sign': '&', 'name': 'and', 'type': 'binary'}, 'xor': {'sign': '^', 'name': 'xor', 'type': 'binary'}, 'or': {'sign': '|', 'name': 'or', 'type': 'binary'}, 'in': {'sign': 'in', 'name': 'contains', 'type': 'binary'}, 'not_in': {'sign': 'not_contains', 'name': 'not_in', 'type': 'binary'}, 'is': {'sign': 'is', 'name': 'is', 'type': 'binary'}, 'is_not': {'sign': 'is_not', 'name': 'is_not', 'type': 'binary'}, 'lt': {'sign': '<', 'name': 'lt', 'type': 'binary'}, 'le': {'sign': '<=', 'name': 'le', 'type': 'binary'}, 'gt': {'sign': '>', 'name': 'gt', 'type': 'binary'}, 'ge': {'sign': '>=', 'name': 'ge', 'type': 'binary'}, 'ne': {'sign': '!=', 'name': 'ne', 'type': 'binary'}, 'eq': {'sign': '==', 'name': 'eq', 'type': 'binary'}, 'bool_and': {'sign': 'and', 'name': 'bool_and', 'type': 'binary'}, 'bool_or': {'sign': 'or', 'name': 'bool_or', 'type': 'binary'}, 'await': {'sign': 'await', 'name': 'await', 'type': 'unary'}, 'neg': {'sign': '-', 'name': 'neg', 'type': 'unary'}, 'pos': {'sign': '+', 'name': 'pos', 'type': 'unary'}, 'inv': {'sign': '~', 'name': 'inv', 'type': 'unary'}, 'not': {'sign': 'not', 'name': 'not', 'type': 'unary'}}
specials+=[operators[w]['sign'] for w in operators]
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
def handle_print(a,p=0):
	c=1
	for w in a:
		if c:
			c=0
		else:
			print('\x1b[33m,\x1b[0m',end='')
		if w['type']=='seq':
			print('\x1b[33m__'+w['name']+'__('+'\x1b[0m',end='')
			handle_print(w['cont'],1)
			print('\x1b[33m)\x1b[0m',end='')
		elif w['type']=='oper':
			print('\x1b[31m'+w['name']+'\x1b[0m',end='')
		elif w['type']=='name':
			print('\x1b[36m'+w['name']+'\x1b[0m',end='')
		elif w['type']=='value':
			print('\x1b[32m'+w['name']+'\x1b[0m',end='')
		else:
			print('\x1b[37m'+w['name']+'\x1b[0m',end='')
	if p==0:
		print()
def handle_parentheses(a,insi=[0,-1]):
	s=[]
	pairs={1:{'(':')','[':']','{':'}'},0:{'(':')','[':']','{':'}','begin':'end'}}
	while a:
		if a[0]['type']=='oper' and a[0]['name'] in pairs[insi[0]].keys():
			s.append({'type':'seq','name':a[0]['name'],'line':a[0]['line'],'cont':[]})
			a=a[1:]
			opened=[]
			if len(a)==0:
				error(s[-1]['line'],'unmatched '+str(s[-1]['name']))
			while opened or not(a[0]['type']=='oper' and a[0]['name']==pairs[insi[0]][s[-1]['name']]):
				if a[0]['type']=='oper' and a[0]['name'] in pairs[insi[0]].keys():
					opened.append(a[0])
					if a[0]['name'] in pairs[1].keys() and insi[0]==0:
						insi[0]=1
						insi[1]=len(opened)-1
				if opened and a[0]['type']=='oper' and a[0]['name']==pairs[insi[0]][opened[-1]['name']]:
					if len(opened)-1==insi[1]:
						insi[0]=0
						insi[1]=-1
					opened.pop()
				s[-1]['cont'].append(a[0])
				a=a[1:]
				if len(a)==0:
					error(s[-1]['line'],'unmatched '+str(s[-1]['name']))
			a=a[1:]
			s[-1]['cont']=handle_parentheses(s[-1]['cont'],[1,-1])
		elif a[0]['type']=='oper' and a[0]['name'] in pairs[insi[0]].values():
			error(a[0]['line'],'unmatched '+str(a[0]['name']))
		else:
			s.append(a[0])
			a=a[1:]
	return s
def handle_calls(a):
	wi=0
	while wi<len(a):
		if len(a)>1+wi and a[wi+0]['type']!='oper' and a[wi+1]['type']=='seq' and a[wi+1]['name'] in '[(':
			s=a[wi:wi+2]
			a[wi:wi+2]=[{'type':'seq','name':{'(':'call','[':'getitem'}[a[wi+1]['name']],'line':a[wi+0]['line'],'cont':[]}]


			if s[0]['type']=='seq':
				s[0]['cont']=handle_calls(s[0]['cont'])
			a[wi]['cont'].append(s[0])
			a[wi]['cont']+=handle_calls(s[1]['cont'])
		else:
			if a[wi+0]['type']=='seq':
				a[wi+0]['cont']=handle_calls(a[wi+0]['cont'])
			wi+=1
	return a
def handle_opers_l2r(a,_ops):
	ops=[operators[w] for w in _ops]
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi+1]['type']=='oper' and a[wi+0]['type']!='oper' and\
				[w for w in ops if w['type']=='binary' and w['sign']==a[wi+1]['name']] and a[wi+2]['type']!='oper':
			s=a[wi:wi+3]
			a[wi:wi+3]=[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi+1]['name']][0]['name'],'line':a[wi+1]['line'],'cont':[]}]
			# a=a[:wi]+[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi+1]['name']][0]['name'],'line':a[wi+1]['line'],'cont':[]}]+a[wi+3:]
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
def handle_opers_r2l(a,_ops,lv=0):
	ops=[operators[w] for w in _ops]
	wi=len(a)
	while wi>0:
		if wi>1 and a[wi-2]['type']=='oper' and a[wi-1]['type']!='oper' and (\
				[w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']] and           a[wi-3]['type']!='oper'  or\
				[w for w in ops if w['type']=='unary'  and w['sign']==a[wi-2]['name']] and (wi==2 or a[wi-3]['type']=='oper') ):

			if  [w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']]:
				s=a[wi-3:wi]
				# a=a[:wi-3]+[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]+a[wi:]
				a[wi-3:wi]=[{'type':'seq','name':[w for w in ops if w['type']=='binary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]
				wi-=2
				if lv:
					s[0]=rvalue2lvalue(s[0])
				if s[-3]['type']=='seq':
					s[-3]['cont']=handle_opers_r2l(s[-3]['cont'],_ops,lv)
				a[wi-1]['cont'].append(s[-3])
				if s[-1]['type']=='seq':
					s[-1]['cont']=handle_opers_r2l(s[-1]['cont'],_ops,lv)
				a[wi-1]['cont'].append(s[-1])
			else:
				s=a[wi-2:wi]
				a[wi-2:wi]=[{'type':'seq','name':[w for w in ops if w['type']=='unary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]
				# a=a[:wi-2]+[{'type':'seq','name':[w for w in ops if w['type']=='unary' and w['sign']==a[wi-2]['name']][0]['name'],'line':a[wi-2]['line'],'cont':[]}]+a[wi:]
				wi-=1
				if s[-1]['type']=='seq':
					s[-1]['cont']=handle_opers_r2l(s[-1]['cont'],_ops,lv)
				a[wi-1]['cont'].append(s[-1])
		else:
			if a[wi-1]['type']=='seq':
				a[wi-1]['cont']=handle_opers_r2l(a[wi-1]['cont'],_ops,lv)
			wi-=1
	return a
def handle_expr_if(a):
	wi=0
	while wi<len(a):
		if wi+4<len(a)  and a[wi+0]['type']!='oper' and a[wi+1]['type']=='oper' and a[wi+1]['name']=='if'\
						and a[wi+2]['type']!='oper' and a[wi+3]['type']=='oper' and a[wi+3]['name']=='else'\
						and a[wi+4]['type']!='oper':
			s=a[wi:wi+5]
			a[wi:wi+5]=[{'type':'seq','name':'expr_if','line':a[wi+1]['line'],'cont':[]}]
			if s[0]['type']=='seq':
				s[0]['cont']=handle_expr_if(s[0]['cont'])
			a[wi]['cont'].append(s[0])
			if s[2]['type']=='seq':
				s[2]['cont']=handle_expr_if(s[2]['cont'])
			a[wi]['cont'].append(s[2])
			if s[4]['type']=='seq':
				s[4]['cont']=handle_expr_if(s[4]['cont'])
			a[wi]['cont'].append(s[4])
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_expr_if(a[wi]['cont'])
			wi+=1
	return a
def handle_lambda(a):
	lop=-1
	wi=0
	while wi<len(a):
		if a[wi]['type']=='oper' and a[wi]['name']=='lambda':
			lop=wi
			wi+=1
		elif wi+1<len(a) and lop>-1 and a[wi]['type']=='oper' and a[wi]['name']==':':
			s=a[lop:wi+2]
			a[lop:wi+2]=[{'type':'seq','name':'lambda','line':a[lop]['line'],'cont':[]}]
			wi=lop
			s[1:-2]=handle_func_args(s[1:-2])
			a[wi]['cont'].append(s[1])
			if s[3]['type']=='seq':
				s[3]['cont']=handle_lambda(s[3]['cont'])
			a[wi]['cont'].append(s[3])
			lop=-1
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_lambda(a[wi]['cont'])
			wi+=1
	return a
def handle_comma(a):
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi+1]['type']=='oper' and a[wi+0]['type']!='oper' and ','==a[wi+1]['name'] and a[wi+2]['type']!='oper':
			s=a[wi:wi+3]
			a[wi:wi+3]=[{'type':'seq','name':'comma','line':a[wi+1]['line'],'cont':[]}]
			if s[-3]['type']=='seq':
				s[-3]['cont']=handle_comma(s[-3]['cont'])
			a[wi]['cont'].append(s[-3])
			if s[-1]['type']=='seq':
				s[-1]['cont']=handle_comma(s[-1]['cont'])
			a[wi]['cont'].append(s[-1])
		elif wi+1<len(a) and a[wi+1]['type']=='oper' and a[wi+0]['type']!='oper' and ','==a[wi+1]['name']:
			s=a[wi:wi+2]
			a[wi:wi+2]=[{'type':'seq','name':'comma','line':a[wi+1]['line'],'cont':[]}]
			if s[0]['type']=='seq':
				s[0]['cont']=handle_comma(s[0]['cont'])
			a[wi]['cont'].append(s[0])
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_comma(a[wi]['cont'])
			wi+=1
	for w in a:
		if w['type']=='seq' and w['name']=='comma' and len(w['cont'])>1:
			while w['cont'][0]['type']=='seq' and w['cont'][0]['name']=='comma' and len(w['cont'][0]['cont'])>1:
				w['cont']=w['cont'][0]['cont']+w['cont'][1:]
	return a
def rvalue2lvalue(a):
	if a['type']=='seq' and a['name']=='getitem':
		a['name']='setitem'
	if a['type']=='seq' and a['name']=='getattr':
		a['name']='setattr'
	return a
def handle_func_args(a):
	a=[w for w in a if not(w['type']=='oper' and w['name']=='/')]
	while [w for w in a if w['type']=='seq' and w['name']=='comma']:
		a=sum([w['cont'] if w['type']=='seq' and w['name']=='comma' else [w] for w in a],[])
	a={'type':'seq','name':'func_args','line':a[0]['line'],'cont':a}
	return [a]
def handle_assign_args(a):
	a=[w for w in a if w['type']!='oper']
	while [w for w in a if w['type']=='seq' and w['name']=='comma']:
		a=sum([w['cont'] if w['type']=='seq' and w['name']=='comma' else [w] for w in a],[])
	a=[rvalue2lvalue(w) for w in a]
	a={'type':'seq','name':'assign_args','line':a[0]['line'],'cont':a}
	return [a]
#///////////////////////////////////////////////////////
def handle_expr_for(a):
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi]['type']!='oper' and a[wi+1]['type']=='oper' and a[wi+1]['name']=='for' and a[wi+2]['type']!='oper':
			e=wi
			while e+2<len(a) and a[e+1]['type']=='oper' and a[e+1]['name'] in ['for','if'] and a[e+2]['type']!='oper':
				e+=2
			s=a[wi:e+1]
			a[wi:e+1]=[{'type':'seq','name':'expr_for','line':s[1]['line'],'cont':[]}]
			for w in s:
				if w['type']=='seq':
					w['cont']=handle_expr_for(w['cont'])
				if w['type']=='oper' and w['name'] in ['for','if']:
					w['name']+='_in_for'
			a[wi]['cont']=s
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_expr_for(a[wi]['cont'])
			wi+=1
	return a
def handle_stat_if(a):
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi]['type']=='oper' and a[wi]['name']=='if' and a[wi+1]['type']!='oper' and a[wi+2]['type']=='oper' and a[wi+2]['name']==':':
			s=a[wi:wi+3]
			a[wi:wi+3]=[{'type':'seq','name':'stat_if','line':s[1]['line'],'cont':[]}]
			for w in s[1:-1]:
				if w['type']=='seq':
					w['cont']=handle_stat_if(w['cont'])
			a[wi]['cont']=s[1:-1]
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_stat_if(a[wi]['cont'])
			wi+=1
	return a
def handle_stat_for(a):
	wi=0
	while wi<len(a):
		if wi+2<len(a) and a[wi]['type']=='oper' and a[wi]['name']=='for':
			e=wi
			while e<len(a) and not(a[e]['type']=='oper' and a[e]['name'] ==':'):
				e+=1
			s=a[wi:e+1]
			a[wi:e+1]=[{'type':'seq','name':'stat_for','line':s[0]['line'],'cont':[]}]
			if len(s)==3:
				if not(s[1]['type']=='seq' and s[1]['name']in['comma','contains']):
					error(s[1]['line'],'unexpected: '+s[1]['name'])
				if s[1]['name']=='contains':
					s=[s[0],s[1]['cont'][0],{'type':'oper','name':'in','line':s[1]['line']},s[1]['cont'][1],s[2]]
				if s[1]['name']=='comma':
					if len(s[1]['cont'])==1:
						...
			z=s[1:-1]
			while 1:
				handle_print(z)
				t=list(filter(lambda q:s[q]['type']=='oper' and a[q]['name']=='in',range(len(z))))
				if t:
					d=t[-1]
					s,d=z[:d],z[d+1:]
					break
				t=list(filter(lambda q:s[q]['type']=='seq' and a[q]['name']=='contains',range(len(z))))
				if t:
					d=t[-1]
					z,x=z[:d],z[d+1:]
					print(s)
					break
				t=list(filter(lambda q:not(s[q]['type']=='seq' and a[q]['name']=='comma'),range(len(z))))
				if t:
					d=t[0]
					t=z[d]
					error(t['line'],'unexpected: '+t['name'])
				z=[w['cont'] for w in z]



			for w in s:
				if w['type']=='seq':
					w['cont']=handle_stat_for(w['cont'])
				if w['type']=='oper' and w['name'] in ['for','if']:
					w['name']+='_in_for'
			a[wi]['cont']=s
		else:
			if a[wi]['type']=='seq':
				a[wi]['cont']=handle_stat_for(a[wi]['cont'])
			wi+=1
	return a
def handle_not(a):
	...#not in is not
text_list=handle_parentheses(text_list)
text_list=handle_opers_l2r(text_list,['getattr'])
text_list=handle_calls(text_list)
text_list=handle_opers_r2l(text_list,['await'])
text_list=handle_opers_r2l(text_list,['pow','await','neg','pos','inv','a_unpack','d_unpack'])
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
text_list=handle_expr_if(text_list)
text_list=handle_comma(text_list)
text_list=handle_lambda(text_list)
text_list=handle_opers_r2l(text_list,['expr_assign','assign','imul','ipow','imatmul','itruediv','ifloordiv','imod','iadd','isub','ilshift','irshift'],1)
text_list=handle_expr_for(text_list)
text_list=handle_stat_if(text_list)
# text_list=handle_stat_for(text_list)
# text_list=handle_opers_l2r(text_list,[';',':','\n'])















if len(argv)==1:
	print()
handle_print(text_list)

