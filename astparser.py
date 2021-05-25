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

if len(argv)>1:
	filename=argv[1]
	text=open(filename).read()
else:
	from sys import stdin
	text=stdin.read()

print()

# body=parse(text).body
# print(*[dump(w,indent=4) for w in body],sep='\n')

par=parse(text)
print(dump(par,indent=4))

indent_sign='+'
indent=0

def generate(astobj):
	global indent
	indent+=1
	if astobj.__class__.__name__=='Module':
		ret=indent_sign*indent+'int main(int argc,char **argv){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='Expr':
		ret=indent_sign*indent+generate(astobj.value)+';\n'
	elif astobj.__class__.__name__=='FunctionDef':
		ret=indent_sign*indent+'any name_'+astobj.name+'(any args, any kwargs){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}\n'+''.join([generate(Assign(targets=[Name(id=astobj.name,ctx=Store())],value=Call(func=w,args=[Name(id=astobj.name,ctx=Load())],keywords=[])))+'\n' for w in astobj.decorator_list[::-1]])
	elif astobj.__class__.__name__=='If':
		ret=indent_sign*indent+'if(any_cast<boolean>('+generate(Call(func=Name(id='python_bool',ctx=Load()),args=[astobj.test],keywords=[]))+')){\n'+''.join([generate(w)+'\n' for w in astobj.body])+indent_sign*indent+'}else{\n'+''.join([indent_sign*indent+generate(w)+'\n' for w in astobj.orelse])+indent_sign*indent+'}'
	elif astobj.__class__.__name__=='Pass':
		ret=indent_sign*indent+'/*pass*/'
	elif astobj.__class__.__name__=='Return':
		ret=indent_sign*indent+'return '+(generate(astobj.value) if astobj.value!=None else generate(Constant(value=None)))+';'
	elif astobj.__class__.__name__=='Delete':
		ret=indent_sign*indent+'python_delete_list('+','.join([generate(w) for w in astobj.targets])+');'
	elif astobj.__class__.__name__=='Assign':
		ret=indent_sign*indent+''.join([generate(w)+'=' for w in astobj.targets])+generate(astobj.value)
	# elif astobj.__class__.__name__=='AugAssign':
	# 	ret=indent_sign*indent+generate(Call(func=Name(id='',ctx=Load()),args=[],keywords=[]))
	elif astobj.__class__.__name__=='Call':
		ret=generate(astobj.func)+'('+generate(List(elts=astobj.args,ctx=Load()))+','+generate(Dict(keys=[Name(id=w.arg,ctx=Load()) for w in astobj.keywords],values=[w.value for w in astobj.keywords]))+')'
	elif astobj.__class__.__name__=='Name':
		ret='name_'+astobj.id
	elif astobj.__class__.__name__=='Constant':
		if type(astobj.value)==type(None):
			ret='python_None'
		if type(astobj.value)==type(0):
			ret='int64_t('+str(astobj.value)+')'
		if type(astobj.value)==type(''):
			ret='std::u32string({'+','.join([str(ord(w)) for w in astobj.value])+'})'
	else:
		ret='\x1b[31m'+dump(astobj,indent=4)+'\x1b[0m'
	indent-=1
	return ret

print()

print(generate(par))

print()