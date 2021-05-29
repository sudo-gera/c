from sys import argv
from functools import reduce
from re import *
from pprint import pprint
from ast import *
def error(q):
# def error(l,q):
# 	print('\x1b[31m[error line '+str(l)+']\x1b[0m',q)
	print('\x1b[31m[error]\x1b[0m',q)
	exit(1)
def lprint(q):
	print('lprint',q)
	return q

filename=None
if len(argv)>1:
	filename=argv[1]
	text=open(filename).read()
else:
	from sys import stdin
	text=stdin.read()
	print()

# body=parse(text).body
# print(*[dump(w,indent=4) for w in body],sep='\n')

random_string_seed=1000000000000000000
def random_string():
	global random_string_seed
	random_string_seed+=1
	return '_'+str(random_string_seed)

text=parse(text)
print(dump(text,indent=4))

indent_sign='\t'
indent=0

to_include=['levels']

debug=0

def generate(astobj):
	# print(dump(astobj,indent=4))
	global indent
	indent+=1
	if astobj.__class__.__name__=='Module':
		ret=indent_sign*indent+'int main(int argc,char **argv){\n'\
		+indent_sign*indent+'python_create_level()\n'\
		+indent_sign*indent+'python_headers\n'\
		+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'python_delete_level()}'
	elif astobj.__class__.__name__=='Expr':
		ret=indent_sign*indent+generate(astobj.value)+';\n'
	elif astobj.__class__.__name__=='FunctionDef':
		if hasattr(astobj,'returns') and generate(astobj.returns)==generate(Constant(value='__simple_function__')):
			fn=random_string()
			ret =indent_sign*indent+'any '+fn+'(any args, any kwargs){\n'\
				+indent_sign*indent+indent_sign+generate(Name(id=astobj.name,ctx=Store()))+'='+fn+';\n'\
				+indent_sign*indent+indent_sign+'python_create_level()\n'\
				+'\n'.join([generate(w) for w in astobj.body])+'\n'\
				+indent_sign*indent+indent_sign+'python_delete_level()}\n'\
				+''.join([generate(Assign(targets=[Name(id=astobj.name,ctx=Store())],value=Call(func=w,args=[Name(id=astobj.name,ctx=Load())],keywords=[])))+'\n' for w in astobj.decorator_list[::-1]])
		else:
			fn=random_string()
			ret =indent_sign*indent+'any '+fn+'(any args, any kwargs){\n'\
				+indent_sign*indent+indent_sign+generate(Name(id=astobj.name,ctx=Store()))+'='+fn+';\n'\
				+indent_sign*indent+indent_sign+'python_create_level()\n'\
				+'\n'.join([generate(w) for w in astobj.body])+'\n'\
				+indent_sign*indent+indent_sign+'python_delete_level()}\n'\
				+''.join([generate(Assign(targets=[Name(id=astobj.name,ctx=Store())],value=Call(func=w,args=[Name(id=astobj.name,ctx=Load())],keywords=[])))+'\n' for w in astobj.decorator_list[::-1]])
	elif astobj.__class__.__name__=='If':
		ret=indent_sign*indent+'if(any_cast<boolean>('+generate(Call(func=Name(id='python_bool',ctx=Load()),args=[astobj.test],keywords=[]))+')){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}else{\n'+''.join([indent_sign*indent+generate(w)+'\n' for w in astobj.orelse])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='While':
		ret=indent_sign*indent+'while(any_cast<boolean>('+generate(Call(func=Name(id='python_bool',ctx=Load()),args=[astobj.test],keywords=[]))+')){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='Pass':
		ret=indent_sign*indent+'/*pass*/'
	elif astobj.__class__.__name__=='Global':
		ret=indent_sign*indent+'python_global('+','.join(astobj.names)+')'
	elif astobj.__class__.__name__=='For':
		ret=indent_sign*indent+'for('+generate(astobj.target)+':python_iterate('+generate(astobj.iter)+')){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='Nonlocal':
		ret=indent_sign*indent+'python_nonlocal('+','.join(astobj.names)+')'
	elif astobj.__class__.__name__=='Return':
		ret=indent_sign*indent+'return '+(generate(astobj.value) if astobj.value!=None else generate(Constant(value=None)))+';'
	# elif astobj.__class__.__name__=='Delete':
	# 	ret=indent_sign*indent+'python_delete_list('+','.join([generate(w) for w in astobj.targets])+');'
	elif astobj.__class__.__name__=='Assign':
		ret=indent_sign*indent+''.join([generate(w)+'=' for w in astobj.targets])+generate(astobj.value)
	# elif astobj.__class__.__name__=='AugAssign':
	# 	ret=indent_sign*indent+generate(Call(func=Name(id='',ctx=Load()),args=[],keywords=[]))
	elif astobj.__class__.__name__=='Call':
		ret=generate(astobj.func)+'('+generate(List(elts=astobj.args,ctx=Load()))+','+generate(Dict(keys=[Name(id=w.arg,ctx=Load()) for w in astobj.keywords],values=[w.value for w in astobj.keywords]))+')'
	elif astobj.__class__.__name__=='List':
		if len(astobj.elts)==0:
			ret='python_create_empty_list()'
		elif len(astobj.elts)==1 and astobj.elts[0].__class__.__name__!='Starred':
			ret='python_create_one_list('+generate(astobj.elts[0])+')'
		else:
			rsum=List(elts=[])
			for w in astobj.elts:
				if w.__class__.__name__=='Starred':
					rsum=BinOp(left=rsum,op=Add(),right=Call(func=Name(id='python_list',ctx=Load()),args=[w.value],keywords=[]))
				else:
					rsum=BinOp(left=rsum,op=Add(),right=List(elts=[w]))
			ret=generate(rsum)
		# ret='+'.join([generate(w) for w in astobj.elts])+')'
		# ret='python_list_generator('+','.join([generate(w) for w in astobj.elts])+')'
	elif astobj.__class__.__name__=='BinOp':
		ret='python_operator_'+astobj.op.__class__.__name__+'('+generate(astobj.left)+','+generate(astobj.right)+')'
	elif astobj.__class__.__name__=='BoolOp':
		ret='python_operator_'+astobj.op.__class__.__name__+'('+','.join([generate(w) for w in astobj.values])+')'
	elif astobj.__class__.__name__=='UnaryOp':
		ret='python_operator_'+astobj.op.__class__.__name__+'('+generate(astobj.operand)+')'
	elif astobj.__class__.__name__=='Compare':
		ret='python_operator_compare('+generate(astobj.left)+''.join([',"'+w[0].__class__.__name__+'",'+generate(w[1]) for w in zip(astobj.ops,astobj.comparators)])
	elif astobj.__class__.__name__=='Name':
		if debug:
			ret=str(astobj.id)
		else:
			ret=('python_get(' if astobj.ctx.__class__.__name__=='Load' else 'python_set(')+generate(Constant(value=astobj.id))+')'
	elif astobj.__class__.__name__=='Constant':
		if debug:
			ret=str(astobj.value)
		else:
			if type(astobj.value)==type(None):
				ret='python_None'
			if type(astobj.value)==type(0):
				ret='int64_t('+str(astobj.value)+')'
			if type(astobj.value)==type(''):
				ret='std::u32string({'+','.join([str(ord(w)) for w in astobj.value])+'})/*'+astobj.value+'*/'
	else:
		ret='\x1b[31m'+dump(astobj,indent=4)+'\x1b[0m'
	indent-=1
	return ret

print()


text=generate(text)
# print(text)

# print()


headers={
	'print':{
		'c++_code':
			'''

			''',
		'python_code':
			'''

			''',
		'depends':
			[],
	},
	'stdc++':{'c++_code':'#include<bits/stdc++.h>','python_code':'','depends':[]},
	'vector':{'c++_code':'#include<vector>','python_code':'','depends':[]},
	'string':{'c++_code':'#include<string>','python_code':'','depends':[]},
	'map':{'c++_code':'#include<map>','python_code':'','depends':[]},
	'any':{'c++_code':'#include<any>','python_code':'','depends':[]},
	'levels':{
		'c++_code':
			r'''
				#define python_level_type_first std::u32string
				#define python_level_type_second std::any
				std::vector<std::map<python_level_type_first,python_level_type_second*>> python_globals;
				#define python_global(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[0][q];\
					
				#define python_nonlocal(q)\
				 	if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){\
						python_locals[q]=0;\
						python_globals[python_globals.size()-1][q]=&(python_locals[q]);\
					}\
					python_globals[python_globals.size()-1][q]=python_globals[python_globals.size()-2][q];
					
				#define python_get(q) (*(python_globals[python_globals.size()-1][q]))

				#define python_set(q) python_set_(q,&python_locals)

				python_level_type_second& python_set_(python_level_type_first q,std::map<python_level_type_first,python_level_type_second> *python_locals_pointer){
					if (python_globals[python_globals.size()-1].find(q) == python_globals[python_globals.size()-1].end()){
						(*python_locals_pointer)[q]=0;
						python_globals[python_globals.size()-1][q]=&((*python_locals_pointer)[q]);
					}
					return *(python_globals[python_globals.size()-1][q]);
				}

				#define python_create_level()\
					python_globals.emplace_back();\
					std::map<python_level_type_first,python_level_type_second> python_locals;

				#define python_delete_level()\
					python_globals.pop_back();
			''',
		'python_code':
			'',
		'depends':
			['vector','string','map','any'],
	},
}


for w in to_include:
	to_include+=headers[w]['depends']
to_include=to_include[::-1]
to_include=reduce(lambda a,s:a+[s] if s not in a else a,to_include,[])
to_include_first=''.join(['\n/*'+'*'*76+'*/\n/*defining '+w+'*/\n'+headers[w]['c++_code']+'\n' for w in to_include])
to_include_second=''.join(['\\\n/*'+'*'*75+'*/\\\n/*defining '+w+'*/\\\n'+headers[w]['python_code']+'\\\n' for w in to_include])
text=to_include_first+'\n'+'#define python_headers\\\n'+to_include_second+'/'*80+'\n//main code\n'+text
print(text)
if filename!=None:
	open(filename+'.cpp','w').write(text)