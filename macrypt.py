from h import *
while 1:
    c=64
    s=''
    s+='\n'+(f'KEY{0:020} | (KEY + 0LLU)')+'\n'
    for w in range(1,c):
        s+=(f'KEY{w:020} | (KEY{w-1:020} {choice("*^+-")+choice([" ","~"])} '+choice([f'KEY{rand(0,w):020}']*int(log(w))+[f'{rand()}LLU'])+f')')+'\n'
    s+=(f'RES | KEY{c-1:020}')
    rc=10000
    d=set()
    nl='\n'
    exec(f'''
for w in range(rc):
    KEY=rand()
    {s.replace('LLU','').replace('|','=').replace(nl,nl+'    ')}
    d.add(RES)
''')
    if len(d)==rc:
        break
print(s.replace('\n','\n#define ').replace('|',''))
print(f'-DKEY={KEY}LLU')
print(f'#if RES=={RES%2**64}LLU')
