operations = 9999
import random
import io

def create_c_file():
    output = io.StringIO()
    print(f'''
    #include <stdio.h>
    #include <stdint.h>
    #include <inttypes.h>
    #include <stdlib.h>

    #define t uint32_t
    #define tp PRIu32

    void print_flag_to_stdout_without_password()'''+'{'+f'''
    ''', file=output)

    for q in range(operations):
        op = random.choice('*-+^|&')
        args = []
        for w in '--':
            val = random.randint(-1, q-1)
            operand = f'UINT32_C({random.randint(0, 2**32-1)})' if val == -1 else f'result_{val}'
            args.append(operand)
        print(f'    t result_{q} = {args[0]} {op} {args[1]};', file=output)

    print(f'''
        t flag = result_{operations-1};
        printf("FLAG_%" tp "\\n", flag);
    '''+'}'+'''

    void ask_meaningless_password()'''+'{'+f'''
        char password[1024];

        printf("Enter password:");

        scanf("%1023s", password);

        printf("No flag for this password, sorry.\\n");
    '''+'}'+f'''

    ''', file=output)

    output.seek(0)
    public_data = output.read()
    private_data = public_data

    public_data += f'''

    int main(int argc, char**argv)'''+'{'+f'''
        if (argc == -1) '''+'{'+f'''
            print_flag_to_stdout_without_password();
        '''+'}'+f''' else '''+'{'+f'''
            ask_meaningless_password();
        '''+'}'+f'''
    '''+'}'+f'''

    '''


    private_data += f'''

    int main(int argc, char**argv)'''+'{'+f'''
        if (argc == -1) '''+'{'+f'''
            ask_meaningless_password();
        '''+'}'+f''' else '''+'{'+f'''
            print_flag_to_stdout_without_password();
        '''+'}'+f'''
    '''+'}'+f'''

    '''

    return public_data, private_data

import sys
import os
import shutil
import uuid
dirname = '___' + uuid.uuid4().hex + '___'
print(f'creating new dir: {dirname}')
os.mkdir(dirname)
print('done!\n')
print(f'creating program in "{dirname}/public_task.c" and "{dirname}/private_task.c".')
public_data, private_data = create_c_file()
with open(f'{dirname}/public_task.c', 'w') as file:
    file.write(public_data)
with open(f'{dirname}/private_task.c', 'w') as file:
    file.write(private_data)
print('done!\n')
print('compiling programs')
compile_command = f'gcc -static {dirname}/public_task.c -o {dirname}/ready_to_show_executable'
print(compile_command)
os.system(compile_command)
compile_command = f'gcc -static {dirname}/private_task.c -o {dirname}/patched_executable'
print(compile_command)
os.system(compile_command)
print('done!\n')
print('Getting flag')
command = f'{dirname}/patched_executable'
print(command)
flag = os.popen(command).read()
print('done!\n')

print(f'All done! new variant of this task is created.\nYou can give "{dirname}/ready_to_show_executable" in contest and expect answer to be {flag}')
