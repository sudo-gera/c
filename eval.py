# #if 0
# from h import *
# from sys import argv
# from functools import reduce
# from re import *
# from keyword import kwlist
# from pprint import pprint
# def error(q):
# 	l=0
# 	print("\x1b[31m[error line "+str(l)+"]\x1b[0m",q)
# 	exit(1)
# def lprint(q):
# 	print("lprint",q)
# 	return q
# if len(argv)>1:
# 	filename=argv[1]
# 	text=open(filename).read()
# else:
# 	from sys import stdin
# 	text=stdin.read()
# text=text.strip()

# filename=argv[1]
# text=open(filename).read()
# text=text.splitlines()
# text=[w for w in text if w.strip()]

# def isdigit(q):
# 	return q.isdigit()

# def arr(*a):
# 	return list(a)

# begin_b=0
# end_b=0

# def args(x):
# 	pass

# def slice(a,begin,end):
# 	return a[begin:end]
# def make():
# 	pass
# #endif

# #define len(...) (__VA_ARGS__).size()

# #define def auto

# #define elif else if

# #define begin_b {
# #define end_b }

# #define args_0
# #define args_1 template<typename T1>
# #define args_2 template<typename T1,typename T2>
# #define args_3 template<typename T1,typename T2,typename T3>
# #define args_4 template<typename T1,typename T2,typename T3,typename T4>
# #define args_5 template<typename T1,typename T2,typename T3,typename T4,typename T5>
# #define args_6 template<typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
# #define args(x) args_##x

# #define make args(1)def slice(const T1&a,long begin,long end){return refdecltype(a)(a.begin()+begin,a.end()+end);}
# make()
# #undef make

# operators={
# 	"mul":	{"sign":	"*",	"name":	"mul",	"type":	"binary"},
# 	"truediv":	{"sign":	"/",	"name":	"truediv",	"type":	"binary"},
# 	"mod":	{"sign":	"%",	"name":	"mod",	"type":	"binary"},
# 	"add":	{"sign":	"+",	"name":	"add",	"type":	"binary"},
# 	"sub":	{"sign":	"-",	"name":	"sub",	"type":	"binary"},
# 	"neg":	{"sign":	"-",	"name":	"neg",	"type":	"unary"},
# 	"pos":	{"sign":	"+",	"name":	"pos",	"type":	"unary"}
# }

# args(1)
# def handle_ev(a):
# 	res=[]
# 	for w in a:
# 		if (w["type"]=="seq"):
# 			if (w["name"]=="add"):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]+t[1]);
# 				end_b
# 			elif (w["name"]=="sub"):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]-t[1]);
# 				end_b
# 			elif (w["name"]=="mul"):
# 				begin_b
# 				t=handle_ev(w["cont"])
# 				res.append(t[0]*t[1])
# 				end_b
# 			elif (w["name"]=="truediv"):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]/t[1]);
# 				end_b
# 			elif (w["name"]=="("):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]);
# 				end_b
# 			elif (w["name"]=="neg"):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(-t[0]);
# 				end_b
# 			elif (w["name"]=="pos"):
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]);
# 				end_b
# 			else:
# 				begin_b
# 				t=handle_ev(w["cont"]);
# 				res.append(t[0]+t[1]);
# 				end_b
# 		else:
# 			begin_b
# 			t=float(w["name"]);
# 			res.append(t);
# 			end_b
# 	return res;
# def handle_parentheses(a,insi=[0,-1]):
# 	s=[]
# 	while (len(a)):
# 		begin_b
# 		if (a[0]["type"]=="oper" and a[0]["name"] =="("):
# 			begin_b
# 			s.append({"type":"seq","name":a[0]["name"],"cont":[]});
# 			a=slice(a,1,len(a))
# 			opened=[];
# 			while (opened or not(a[0]["type"]=="oper" and a[0]["name"]==')')):
# 				begin_b
# 				if (a[0]["type"]=="oper" and a[0]["name"] == '('):
# 					begin_b
# 					opened.append(a[0])
# 					if a[0]["name"] == '(' and insi[0]==0:
# 						begin_b
# 						insi[0]=1
# 						insi[1]=len(opened)-1
# 						end_b
# 					end_b
# 				if (opened and a[0]["type"]=="oper" and a[0]["name"]==')'):
# 					begin_b
# 					if (len(opened)-1==insi[1]):
# 						begin_b
# 						insi[0]=0
# 						insi[1]=-1
# 						end_b
# 					opened.pop()
# 					end_b
# 				s[-1]["cont"].append(a[0])
# 				a=slice(a,1,len(a))
# 				end_b
# 			a=slice(a,1,len(a))
# 			s[-1]["cont"]=handle_parentheses(s[-1]["cont"],[1,-1])
# 			end_b
# 		else:
# 			begin_b
# 			s.append(a[0])
# 			a=slice(a,1,len(a))
# 			end_b
# 		end_b
# 	return s;
# def handle_opers_l2r(a,_ops):
# 	ops=[]
# 	for w in _ops:
# 		ops.append(operators[w]);
# 	wi=0
# 	while (wi<len(a)):
# 		if wi+2<len(a) and a[wi+1]["type"]=="oper" and a[wi+0]["type"]!="oper" and\
# 				[w for w in ops if w["type"]=="binary" and w["sign"]==a[wi+1]["name"]] and a[wi+2]["type"]!="oper":
# 			s=slice(a,wi,wi+3)
# 			a=a[:wi]+[{"type":"seq","name":[w for w in ops if w["type"]=="binary" and w["sign"]==a[wi+1]["name"]][0]["name"],"cont":[]}]\
# 			+a[wi+3:];
# 			if s[-3]["type"]=="seq":
# 				s[-3]["cont"]=handle_opers_l2r(s[-3]["cont"],_ops);
# 			a[wi]["cont"].append(s[-3])
# 			if s[-1]["type"]=="seq":
# 				s[-1]["cont"]=handle_opers_l2r(s[-1]["cont"],_ops);
# 			a[wi]["cont"].append(s[-1])
# 		else:
# 			if a[wi]["type"]=="seq":
# 				a[wi]["cont"]=handle_opers_l2r(a[wi]["cont"],_ops);
# 			wi+=1
# 	return a
# def handle_opers_r2l(a,_ops):
# 	ops=[]
# 	for w in _ops:
# 		ops.append(operators[w])
# 	wi=len(a)
# 	while wi>0:
# 		if wi>1 and a[wi-2]["type"]=="oper" and a[wi-1]["type"]!="oper" and (\
# 				[w for w in ops if w["type"]=="binary" and w["sign"]==a[wi-2]["name"]] and           a[wi-3]["type"]!="oper"  or\
# 				[w for w in ops if w["type"]=="unary"  and w["sign"]==a[wi-2]["name"]] and (wi==2 or a[wi-3]["type"]=="oper") ):

# 			if  [w for w in ops if w["type"]=="binary" and w["sign"]==a[wi-2]["name"]]:
# 				s=a[wi-3:wi]
# 				a=a[:wi]+[{"type":"seq","name":[w for w in ops if w["type"]=="binary" and w["sign"]==a[wi-2]["name"]][0]["name"],"cont":[]}]\
# 				+a[wi+3:]
# 				wi-=2
# 				if (s[-3]["type"]=="seq"):
# 					s[-3]["cont"]=handle_opers_r2l(s[-3]["cont"],_ops)
# 				a[wi-1]["cont"].append(s[-3])
# 				if (s[-1]["type"]=="seq"):
# 					s[-1]["cont"]=handle_opers_r2l(s[-1]["cont"],_ops)
# 				a[wi-1]["cont"].append(s[-1])
# 			else:
# 				s=a[wi-2:wi]
# 				a[wi-2:wi]=[{"type":"seq","name":[w for w in ops if w["type"]=="unary" and w["sign"]==a[wi-2]["name"]][0]["name"],"cont":[]}]
# 				wi-=1
# 				if (s[-1]["type"]=="seq"):
# 					s[-1]["cont"]=handle_opers_r2l(s[-1]["cont"],_ops)
# 				a[wi-1]["cont"].append(s[-1])
# 		else:
# 			if (a[wi-1]["type"]=="seq"):
# 				a[wi-1]["cont"]=handle_opers_r2l(a[wi-1]["cont"],_ops)
# 			wi-=1
# 	return a


# args(1)
# def run(text):
# 	text_list=[]
# 	for w in text:
# 		if (isdigit(w)):
# 			text_list.append({"name":w,"type":"value"});
# 		else:
# 			text_list.append({"name":w,"type":"oper"});

# 	text_list=handle_parentheses(text_list)
# 	text_list=handle_opers_r2l(text_list,["neg","pos"])
# 	text_list=handle_opers_l2r(text_list,["mul","truediv","mod"])
# 	text_list=handle_opers_l2r(text_list,["add","sub"])

# 	return(handle_ev(text_list)[0])

# a=open('test.py').read().splitlines()
# for w in a:
# 	try:
# 		z=run(w)
# 	except:
# 		ic(w)
# 		exit()
# 	try:
# 		x=eval(w)
# 	except:
# 		ic(w)
# 		exit()
# 	if z!=x:
# 		ic(w,z,x)
# 		exit()
print(int(eval(input())))
