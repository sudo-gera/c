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

print(dump(parse(text),indent=4))

indent_sign='\t'
indent=-1

to_include=['levels']

def make_comment(q):
	return '/*'+str(q).replace('*/','*\\/')+'*/'

debug=0

main_text_converted=0

def generate(astobj):
	print(dump(astobj,indent=4))
	global indent
	indent+=1
	# if astobj.__class__.__name__=='Module':
	# 	ret=indent_sign*indent+'int main(int argc,char **argv){\n'\
	# 	+indent_sign*indent+indent_sign+'python_create_level()\n'\
	# 	+indent_sign*indent+indent_sign+'python_headers\n'\
	# 	+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+indent_sign+'python_delete_level()}'
	if 0:
		ret=''
	elif astobj.__class__.__name__=='Expr':
		ret=indent_sign*indent+generate(astobj.value)+';\n'
	elif astobj.__class__.__name__=='FunctionDef':
		if hasattr(astobj,'returns') and generate(astobj.returns)==generate(Constant(value='__simple_function__')):
			pass
		fn=random_string()
		ret =indent_sign*indent+'any '+fn+'(std::any args, std::any kwargs){\n'\
			+indent_sign*indent+indent_sign+generate(Name(id=astobj.name,ctx=Store()))+'='+fn+';\n'\
			+indent_sign*indent+indent_sign+'python_create_level()\n'\
			+'\n'.join([generate(w) for w in astobj.body])+'\n'\
			+indent_sign*indent+indent_sign+'python_delete_level()}\n'\
			+''.join([generate(Assign(targets=[Name(id=astobj.name,ctx=Store())],value=Call(func=w,args=[Name(id=astobj.name,ctx=Load())],keywords=[])))+'\n' for w in astobj.decorator_list[::-1]])
	elif astobj.__class__.__name__=='If':
		to_include.append('bool')
		ret=indent_sign*indent+'if(std::any_cast<bool>(__python__bool('+generate(astobj.test)+'))){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}else{\n'+''.join([indent_sign*indent+generate(w)+'\n' for w in astobj.orelse])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='While':
		to_include.append('bool')
		ret=indent_sign*indent+'while(std::any_cast<bool>(__python__bool('+astobj.test+'))){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}'
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
	elif astobj.__class__.__name__=='Delete':
		to_include.append('debug_str')
		to_include.append('iostream')
		# ret=indent_sign*indent+'python_delete_list('+','.join([generate(w) for w in astobj.targets])+');'
		ret=indent_sign*indent+'std::cout<<'+'<<" "<<'.join(['python_debug_str('+generate(w)+')' for w in astobj.targets])+'<<std::endl;'
	elif astobj.__class__.__name__=='Assign':
		ret=indent_sign*indent+''.join([generate(w)+'=' for w in astobj.targets])+generate(astobj.value)+';'
	# elif astobj.__class__.__name__=='AugAssign':
	# 	ret=indent_sign*indent+generate(Call(func=Name(id='',ctx=Load()),args=[],keywords=[]))
	elif astobj.__class__.__name__=='Call':
		if astobj.func.__class__.__name__=='Name' and astobj.func.id.startswith('__python__'):
			ret=generate(astobj.func)+'('+','.join([generate(w) for w in astobj.args])+')'			
		else:
			ret='python_call('+generate(astobj.func)+','+generate(List(elts=astobj.args,ctx=Load()))+','+generate(Dict(keys=[Name(id=w.arg,ctx=Load()) for w in astobj.keywords],values=[w.value for w in astobj.keywords]))+')'
	elif astobj.__class__.__name__=='List':
		if len(astobj.elts)==0:
			ret='python_create_empty_list()'
		elif len(astobj.elts)==1 and astobj.elts[0].__class__.__name__!='Starred':
			ret='python_create_one_list('+generate(astobj.elts[0])+')'
		else:
			rsum=List(elts=[])
			for w in astobj.elts:
				if w.__class__.__name__=='Starred':
					rsum=BinOp(left=rsum,op=Add(),right=Call(func=Name(id='__python__list',ctx=Load()),args=[w.value],keywords=[]))
				else:
					rsum=BinOp(left=rsum,op=Add(),right=List(elts=[w]))
			ret=generate(rsum)
	elif astobj.__class__.__name__=='Set':
		if len(astobj.elts)==0:
			ret='python_create_empty_set()'
		elif len(astobj.elts)==1 and astobj.elts[0].__class__.__name__!='Starred':
			ret='python_create_one_set('+generate(astobj.elts[0])+')'
		else:
			rsum=List(elts=[])
			for w in astobj.elts:
				if w.__class__.__name__=='Starred':
					rsum=BinOp(left=rsum,op=Add(),right=Call(func=Name(id='__python__set',ctx=Load()),args=[w.value],keywords=[]))
				else:
					rsum=BinOp(left=rsum,op=Add(),right=List(elts=[w]))
			ret=generate(rsum)
	elif astobj.__class__.__name__=='Dict':
		retlist=List(elts=[])
		for w in zip(astobj.keys,astobj.values):
			if w[0]==None:
				retlist.elts.append(Starred(value=Call(func=Name(id='python_dict_to_list_of_pairs',ctx=Load()),args=[Call(func=Name(id='__python__dict',ctx=Load()),args=[w[1]],keywords=[])],keywords=[]),ctx=Load()))
			else:
				retlist.elts.append(List(elts=list(w)))
		ret='python_list_of_pairs_to_dict('+generate(retlist)+')'
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
			chn=astobj.id
			if chn.startswith('__python__'):
				chn=chn[len('__python__'):]
			if chn.startswith('python__builtins__'):
				chn=chn[len('python__builtins__'):]
			global main_text_converted
			if main_text_converted==0 and chn in builtins:
				to_include.append(chn)
			if astobj.id.startswith('__python__'):
				ret=str(astobj.id)
			else:
				ret=('python_get(' if astobj.ctx.__class__.__name__!='Store' else 'python_set(')+generate(Constant(value=astobj.id))+')'
	elif astobj.__class__.__name__=='Constant':
		if debug:
			ret=str(astobj.value)
		else:
			if type(astobj.value)==type(None):
				to_include.append('None')
				ret='python_None'
			if type(astobj.value)==type(0):
				ret='int64_t('+str(astobj.value)+')'
			if type(astobj.value)==type(''):
				to_include.append('string')
				ret='std::u32string({'+','.join([str(ord(w)) for w in astobj.value])+'})'+make_comment(astobj.value)
	else:
		ret='\x1b[31m'+dump(astobj,indent=4)+'\x1b[0m'
	indent-=1
	return ret


def convert(q,a=1):
	if a:
		while '\n' in q[:-len(q.lstrip())]:
			q=q[1:]
		while '\r' in q[:-len(q.lstrip())]:
			q=q[1:]
		l=(len(q)-len(q.lstrip()))
		q=q.split('\n')
		q='\n'.join([w[l:] for w in q])
	return '\n'.join([generate(w) for w in parse(q).body])+'\n'


# builtins=['__import__', 'abs', 'all', 'any', 'ascii', 'bin', 'bool', 'breakpoint', 'bytearray', 'bytes', 'callable', 'chr', 'classmethod', 'compile', 'complex', 'delattr', 'dict', 'dir', 'divmod', 'enumerate', 'eval', 'exec', 'filter', 'float', 'format', 'frozenset', 'getattr', 'globals', 'hasattr', 'hash', 'help', 'hex', 'id', 'input', 'int', 'isinstance', 'issubclass', 'iter', 'len', 'list', 'locals', 'map', 'max', 'memoryview', 'min', 'next', 'object', 'oct', 'open', 'ord', 'pow', 'print', 'property', 'range', 'repr', 'reversed', 'round', 'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str', 'sum', 'super', 'tuple', 'type', 'vars', 'zip']
builtins=  [              'abs', 'all', 'any',          'bin', 'bool',               'bytearray', 'bytes',             'chr',                                                                'divmod',                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ]

text=convert(text,a=0)


main_text_converted=1

headers={
	'None':{
		'c++_code':
			'''
				class python_NoneType{};
				python_NoneType python_None;
			''',
		'python_code':'',
		'depends':[]
	},
	'builtins__wrapper':{
		'c++_code':
			'''
			template<typename t>
			class __python__builtins__wrapper{
			public:
				t d;
				__python__builtins__wrapper(t f){
					d=f;
				}
				std::any operator()(std::any q,std::any w){
					auto s=python_iterate(q);
					vector<std::any> a(s.begin(),s.end());
					if (a.size()==0){
						return d();
					}
					if (a.size()==1){
						return d(a[0]);
					}
					if (a.size()==2){
						return d(a[0],a[1]);
					}
					if (a.size()==3){
						return d(a[0],a[1],a[2]);
					}
					if (a.size()==4){
						return d(a[0],a[1],a[2],a[3]);
					}
					if (a.size()==5){
						return d(a[0],a[1],a[2],a[3],a[4]);
					}
					if (a.size()==6){
						return d(a[0],a[1],a[2],a[3],a[4],a[5]);
					}
					if (a.size()==7){
						return d(a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
					}
					if (a.size()==8){
						return d(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
					}
				}
			};
			''',
		'python_code':'',
		'depends':['any','vector']
	},
	'abs':{
		'c++_code':
			'''
			std::any __python___abs(std::any a){
				{python_iftype(int){
					return std::abs(s);
				}
				}
				{python_iftype(int64_t){
					return std::abs(s);
				}
				}
				{python_iftype(long float){
					return std::fabs(s);
				}
				}
			}
			''',
		'python_code':
			'''
			python__builtins__abs      =__python__builtins__wrapper(__python__abs)
			''',
		'depends':['iftype','any','builtins__wrapper','cmath']
	},
	'all':{
		'c++_code':
			'''
			std::any __python__all(std::any a){
				for (auto w:python_iterate(a)){
					if(!std::any_cast<bool>(__python__bool(w))){
						return false;
					}
				}
				return true;
			}
			''',
		'python_code':
			'''
			python__builtins__all      =__python__builtins__wrapper(__python__all)
			''',
		'depends':['any','builtins__wrapper']
	},
	'any':{
		'c++_code':
			'''
			std::any __python__any(std::any a){
				for (auto w:python_iterate(a)){
					if(std::any_cast<bool>(__python__bool(w))){
						return true;
					}
				}
				return false;
			}
			''',
		'python_code':
			'''
				python__builtins__any      =__python__builtins__wrapper(__python__any)
			''',
		'depends':['any','builtins__wrapper']
	},
	'bin':{
		'c++_code':
			'''
			std::any __python__bin(any a){
				u32string f;
				int64_t d=std::any_cast<int64_t>(a);
				int64_t s=d<0?1:0;
				d=abs(d);
				while (d){
					f.push_back(d%2+'0');
					d/=2;
				}
				if (s){
					f=u32string({'-'})+f;
				}
				return f;
			}
			''',
		'python_code':
			'''
				python__builtins__bin      =__python__builtins__wrapper(__python__bin)
			''',
		'depends':['any','cmath','builtins__wrapper','stirng']
	},
	'bool':{
		'c++_code':
			'''
			std::any __python__bool(std::any a=python_None){
				{python_iftype(a,python_NoneType){
					return false;
				}
				}
				{python_iftype(a,int){
					return s!=0;
				}
				}
				{python_iftype(a,int64_t){
					return s!=0;
				}
				}
				{python_iftype(a,std::string){
					return s.size()!=0;
				}
				}
				{python_iftype(a,std::u32string){
					return s.size()!=0;
				}
				}
			}
			''',
		'python_code':
			'''
				python__builtins__bool     =__python__builtins__wrapper(__python__bool)
			''',
		'depends':['iftype','any','builtins__wrapper','None']
	},
	'bytearray':{
		'c++_code':
			'''
			std::any __python__bytearray(std::any q=std::string(),std::any w=std::string()){
				{iftype(q,std::string){
					return q;
				}
				}
				{iftype(q,std::u32string){
					return to_u8(q);
				}
				}
				{iftype(q,int64_t){
					vector<char> a(t);
					return std::string(a.begin(),a.end());
				}
				}
				auto a=python_iterate(q)
				return std::string(a.begin(),a.end());
			}
			''',
		'python_code':
			'''
				python__builtins__bytearray=__python__builtins__wrapper(__python__bytearray)
			''',
		'depends':['iftype','any','unicode_convert','builtins__wrapper','string']
	},
	'bytes':{
		'c++_code':
			'''
			std::any __python__bytes(std::any q=std::string(),std::any w=python_None,std::any e=python_None){
				{iftype(q,std::string){
					return q;
				}
				}
				{iftype(q,std::u32string){
					return to_u8(q);
				}
				}
				{iftype(q,int64_t){
					vector<char> a(t);
					return std::string(a.begin(),a.end());
				}
				}
				auto a=python_iterate(q)
				return std::string(a.begin(),a.end());
			}
			''',
		'python_code':
			'''
				python__builtins__bytes    =__python__builtins__wrapper(__python__bytes)
			''',
		'depends':['iftype','any','unicode_convert','builtins__wrapper','string']
	},
	'chr':{
		'c++_code':
			'''
			std::any __python__chr(std::any q){
				return std::u32string({chr(std::any_cast<int>(q))});
			}
			''',
		'python_code':
			'''
				python__builtins__chr      =__python__builtins__wrapper(__python__chr)
			''',
		'depends':['any','unicode_convert','builtins__wrapper','string']
	},
	'divmod':{
		'c++_code':
			'''
			std::any __python__divmod(std::any q,std::any w){
				ret=vector<std::any>();
				{python_iftype(q,int64_t)
					auto d=s;
					{python_iftype(w,int64_t){
						ret[0]=d/s;
						ret[1]=d%s;
					}
				}
				if (ret.size()==0){
					q=__python__float(q);
					w=__python__float(w);
					auto e=std::any_cast<long double>(q);
					auto r=std::any_cast<long double>(w);
					auto t=floor(e/r);
					ret[0]=t;
					ret[1]=e-t*r;
				}
				return ret;
			}
			''',
		'python_code':
			'''
				python__builtins__divmod   =__python__builtins__wrapper(__python__divmod)
			''',
		'depends':['iftype','any','cmath','builtins__wrapper']
	},
	'unicode_convert':{
		'c++_code':
			r'''
				char32_t chr(int64_t q){
					if(q<(1<<7)){
						return ((q&127)<<0);
					}
					if(q<(1<<11)){
						return 49280+((q&1984)<<2)+((q&63)<<0);
					}
					if(q<(1<<16)){
						return 14712960+((q&61440)<<4)+((q&4032)<<2)+((q&63)<<0);
					}
					if(q<(1<<21)){
						return 4034953344+((q&1835008)<<6)+((q&258048)<<4)+((q&4032)<<2)+((q&63)<<0);
					}
					return 0;
				}

				int64_t ord(char32_t q){
					int64_t r=0;
					int w,e;
					for (w=3*8;w>-1;w-=8){
						int started=0;
						for (e=7;e>-1;--e){
							if (started==0 and (q&(1<<(w+e)))==0){
								started=1;
							} else
							if (started){
								r=(r<<1)+!!(q&(1<<(w+e)));
							}
						}
					}
					return r;
				}

				std::u32string to_u32(std::string q){
					std::u32string r;
					for(int64_t w=0;w<q.size();++w){
						if ((q[w]&(0b10000000))==0){
							r.push_back(((int32_t(uint8_t(q[w]))<<0)));
						}
						if ((q[w]&(0b11100000))==0b11000000 and w<q.size()-1){
							r.push_back(((int32_t(uint8_t(q[w]))<<8)+(int32_t(uint8_t(q[w+1]))<<0)));
						}
						if ((q[w]&(0b11110000))==0b11100000 and w<q.size()-2){
							r.push_back(((int32_t(uint8_t(q[w]))<<16)+(int32_t(uint8_t(q[w+1]))<<8)+(int32_t(uint8_t(q[w+2]))<<0)));
						}
						if ((q[w]&(0b11111000))==0b11110000 and w<q.size()-3){
							r.push_back(((int32_t(uint8_t(q[w]))<<24)+(int32_t(uint8_t(q[w+1]))<<16)+(int32_t(uint8_t(q[w+2]))<<8)+(int32_t(uint8_t(q[w+3]))<<0)));
						}
					}
					for(auto &w:r){
						w=ord(w);
					}
					return r;
				}

				std::string to_u8(std::u32string q){
					for(auto &w:q){
						w=chr(w);
					}	
					std::string r;
					for(auto w:q){
						if (w&0b11111111000000000000000000000000){
							r.push_back((w&0b11111111000000000000000000000000)>>24);
						}
						if (w&0b111111110000000000000000){
							r.push_back((w&0b111111110000000000000000)>>16);
						}
						if (w&0b1111111100000000){
							r.push_back((w&0b1111111100000000)>>8);
						}
						r.push_back(w&0b11111111);
					}
					return r;
				}
			''',
		'python_code':'',
		'depends':['string']
	},
	'debug_str':{
		'c++_code':
		'''
				std::string python_debug_str(std::any a){
					std::string d="type not found";
					{python_iftype(a,int)d=s;}
					{python_iftype(a,std::string)d=s;}
					{python_iftype(a,std::u32string)d=to_u8(s);}
					{python_iftype(a,int)d=std::to_string(s);}
					{python_iftype(a,int64_t)d=std::to_string(s);}
					return d;
				}
		''',
		'python_code':'',
		'depends':
			['iftype','any','unicode_convert'],
	},
	'iftype':{
		'c++_code':
		'''
				#define python_iftype(a,type_) type_ s;if (a.type()==typeid(std::declval<type_>())){s=std::any_cast<type_>(a);}if (a.type()==typeid(std::declval<type_>()))
		''',
		'python_code':'',
		'depends':['any'],
	},
	'stdc++':{'c++_code':'#include<bits/stdc++.h>','python_code':'','depends':[]},
	'vector':{'c++_code':'#include<vector>','python_code':'','depends':[]},
	'string':{'c++_code':'#include<string>','python_code':'','depends':[]},
	'iostream':{'c++_code':'#include<iostream>','python_code':'','depends':[]},
	'map':{'c++_code':'#include<map>','python_code':'','depends':[]},
	'any':{'c++_code':'#include<any>','python_code':'','depends':[]},
	'cmath':{'c++_code':'#include<cmath>','python_code':'','depends':[]},
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
		'python_code':'',
		'depends':
			['vector','string','map','any'],
	},
}




for w in to_include:
	to_include+=headers[w]['depends']
to_include=to_include[::-1]
to_include=reduce(lambda a,s:a+[s] if s not in a else a,to_include,[])
to_include_first=''.join(['\n/*'+'*'*76+'*/\n/*defining '+w+'*/\n'+headers[w]['c++_code']+'\n' for w in to_include])
to_include_second=''.join(['\n/*'+'*'*76+'*/\n/*defining '+w+'*/\n'+convert(headers[w]['python_code'])+'\n' for w in to_include])
text=to_include_first+'\n'\
	+'/'*80+'\n//main code\n'\
	+'int main(int argc,char **argv){\n'\
	+'python_create_level()\n'\
	+to_include_second\
	+'/'*80+'\n//main code\n'\
	+text\
	+'python_delete_level()}'

# text=to_include_first+'\n'+'/'*80+'\n//main code\n'+text
print(text)
if filename!=None:
	open(filename+'.cpp','w').write(text)