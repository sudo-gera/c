from h import *
while 1:
    c=64
    s=''
    s+='\n'+(f'KEY{0:020} | (KEY + 0LLU)')+'\n'
    for w in range(1,c):
        s+=(f'KEY{w:020} | (KEY{w-1:020} {choice("*^*^*^+-")+" "+choice("+~-")} '+choice([f'KEY{rand(0,w):020}']*int(log(w))+[f'{rand(10000000000000000000,2**64)}LLU'])+f')')+'\n'
    s+=(f'RES | KEY{c-1:020}')
    rc=16777216
    d=set()
    nl='\n'
    p2=2**64-1
    brl='{'
    brr='}'
    bs='\\'
    open('macrypt.c','w').write(f'''
#include <stdio.h>
#include <stdlib.h>
typedef long long unsigned llu;
int main(){brl}
    llu KEY={rand()}LLU;
    for (llu q=0;q<{rc};++q){brl}
        KEY ^= KEY << 21;
        KEY ^= KEY >> 35;
        KEY ^= KEY << 4;
    {s.replace(nl,';'+nl+'    llu ').replace('|','=')};
    printf("%llx{bs}n",RES);
    {brr}
{brr}
''')
    assert system('gcc -O2 macrypt.c -o macrypt.exe')==0
    y=subprocess.run('./macrypt.exe',stdout=PIPE).stdout
    if len(set(y.split()))==rc:
        rc=65536
        d=set()
        exec(f'''
for w in range(rc):
    KEY=rand()
    {s[1:].replace('LLU','').replace('|','=').replace(nl,'&p2'+nl+'    ')}
    d.add(RES)
''')
        if len(d)==rc:
            break


print(s.replace('\n','\n#define ').replace('|',''))
print(f'-DKEY={KEY}LLU')
print(f'#if RES=={RES%2**64}LLU')
