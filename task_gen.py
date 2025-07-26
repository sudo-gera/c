operations = 20
import random

print(f'''
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
      
#define t uint32_t
#define tp PRIu32

void print_flag_to_stdout_without_password()'''+'{'+f'''
''')

for q in range(operations):
    op = random.choice('*-+^|&')
    args = []
    for w in '--':
        val = random.randint(-1, q-1)
        operand = f'UINT32_C({random.randint(0, 2**32-1)})' if val == -1 else f'result_{val}'
        args.append(operand)
    print(f'    t result_{q} = {args[0]} {op} {args[1]};')

print(f'''
    t flag = result_{operations-1};
    printf("FLAG_%" tp "\\n", flag);
'''+'}'+'''

void ask_meaningless_password()'''+'{'+f'''
    char password[1024]; // Buffer of size 50

    printf("Enter password:");
    scanf("%49s", password); 

    printf("No flag for this password, sorry.\\n");
'''+'}'+f'''

int main(int argc, char**argv)'''+'{'+f'''
    if (argc == -1) '''+'{'+f'''
        print_flag_to_stdout_without_password();
    '''+'}'+f''' else '''+'{'+f'''
        ask_meaningless_password();
    '''+'}'+f'''
'''+'}'+f'''

''')
