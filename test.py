from h import *
c=100
print(f'#define KEY{0:020} KEY')
for w in range(1,c):
    print(f'#define KEY{w:020} (KEY{w-1:020} {choice("*^^^+-")} '+choice([f'KEY{rand(0,w):020}',f'{rand()}LLU'])+f')')
print(f'#define RES KEY{c-1:020}')
