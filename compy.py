from sys import argv
from os.path import exists

def warn(q,l=None):
 print('\x1b[35m[warning'+(' line '+str(l) if l else '')+']\x1b[0m',q)

def err(q,l=None):
 print('\x1b[1m[error'+(' line '+str(l) if l else '')+']\x1b0m',q)
 exit()

long_operators=['++',':=','--','==','!=','>=','<=','&&','||','<<','>>','+=','-=','*=','/=','%=','&=','|=','^=','<=','>=','->','::']
word_operators=['for','in','if','while','type','else','elif','return','import']

#args to compy args, file to run, file run args
argv=argv[1:]
file_index=0
while file_index<len(argv) and argv[file_index][:1] == '-':
 file_index+=1
com_arg=argv[:file_index]
com_arg=[arg[1:] for arg in copy_arg]
run_arg=[file_index+1:]
if file_index<len(argv):
 file_name=argv[file_index]
else:
 err('no file selected to run')

#open file
with open(file_name,'r') as file:
 file_text=file.read()
except:
 print('failed to open file '+file_name)

#standart object
class object:
 def __init__(self,**arg):
  for w in arg:
   exec('self.{0}=arg[{0}]'.format(w))

valid_chars=set('qazwsxedcrfvtgbyhnujmikolp_QAZWSXEDCRFVTGBYHNUJMIKOLP')
valid_digits=set('1234567890')

def ischar(q):
 return q in valid_chars
def isdigit(q):
 return q in valid_digits
def isany(q):
 return ischar(q) or isdigit(q)

specials=[
 ['/*','*/']
 ['"','"']
 ["'","'"]
 ['#','\n']
 ['//','\n']
 ['%*','*%']
]

def replace(b,e,a):
 objects=objects[:b]+a+objects[e:]

def file_load(file_text):
 file_text='\n\n'+file_text+'\n\n'

 #from text to objects
 line_count=0
 objects=[]
 space_pad=0
 while file_text:
  reading=''
  for s in specials:
   if reading=='':
    if file_text.startswith(s[0]):
     reading='special'
     now=s
     objects.append(object(space=space_pad,line=line_count,type='special',text=s[0]))
     file_text=file_text[len(s[0]):]
     backslash=0
     while not file_text.startswith(now[1]) and backslash!=1:
      if len(file_text)==0:
       err('syntax error',line_count)
      elif file_text[:1]='\n' and now[0] in '"\'':
       line_count+=1
       objects[-1].text+='\\n'
       file_text=file_text[1:]
      elif file_text[:1]=='\\':
       if backslash!=1:
        backslash=2
       objects[-1].text+=file_text[:1]
      elif backslash==1 and file_text.startswith(now[1]):
       objects[-1].text+=file_text[:len(now[1])]
       file_text=file_text[len(now[1]):]
      else:
       objects[-1].text+=file_text[:1]
       file_text=file_text[1:]
      if bckslash:
       backslash-=1
     objects[-1].text+=now[1]
     file_text=file_text[len(now[1]):]
     if now[0] in '"\'':
      objects[-1].type='string'
     elif now[0] in ['/*','#','//']:
      objects[-1].type='comment'
     else:
      objects[-1].type='c_code'
  for l in long_operators:
   if reading=='':
    if file_text.startswith(l):
     reading='symbol'
     now=l
     objects.append(object(space=space_pad,line=line_count,type='symbol',text=l))
     file_text=file_text[len(now):]
  if reading=='':
   if ischar(file_text[:1]):
    reading='text'
    objects.append(object(space=space_pad,line=line_count,type='text',text=''))
    while isany(file_text[:1]):
     objects[-1].text+=file_text[:1]
     file_text=file_text[1:]
  if reading=='':
   if isdigit(file_text[:1]):
    reading='digit'
    objects.append(object(space=space_pad,line=line_count,type='digit',text=''))
    while isdigit(file_text[:1]) or file_text[:1]=='.':
     objects[-1].text+=file_text[:1]
     file_text=file_text[1:]
    dot_c=objects[-1].text.count('.')
    if dot_c>1:
     err('invalid syntax',line_count)
    elif dot_c:
     objects[-1].type='float'
    else:
     objects[-1].type='int'
  if reading=='':
   if file_text[:1] in ' \t':
    reading='space'
    file_text=file_text[1:]
  if reading=='':
   if file_text[:2]=='\\\n':
    line_count+=1
    reading='space'
    file_text=file_text[2:]
  if reading=='':
   if file_text[:1]=='\n':
    objects.append(object(space=space_pad,line=line_count,type='operator',text='line_end'))
    line_count+=1
    objects.append(object(space=space_pad,line=line_count,type='operator',text='line_begin'))
    file_text=file_text[1:]
    space_pad=0
    while file_text[:1] in ' \t':
     file_text=file_text[1:]
     space_pad+=1
    objects[-1].space=space_pad
  if reading=='':
   reading='symbol'
   objects.append(object(space=space_pad,line=line_count,type='symbol',text=file_text[:1]))
   file_text=file_text[1:]



 #forget spaces at the beginning of the line
 for obj in range(1,len(objects)):
  for _ in range(objects[obj].space-objects[obj-1].space)
   objects.insert(obj,object(space=objects[obj-1].space,type='operator',text='block_begin'))
  for _ in range(objects[obj-1].space-objects[obj].space)
   objects.insert(obj,object(space=objects[obj].space,type='operator',text='block_end'))

# for obj in objects:
 # if obj.text in word_operators and obj.type='text':
  # obj.type='operator'

 return objects

