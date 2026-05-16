# from random import randint, choice
from random import Random
from math import log
from subprocess import PIPE
from os import system
import os
import sys
import subprocess

os.chdir(
    os.path.dirname(
        os.path.realpath(
            __file__
        )
    )
)

def rand(q: int = 2**64, e: int | None = None) -> int:
    if e is not None:
        q, e = e, q
    else:
        e = 0
    assert q - e
    return randint(e, q - 1)

def key_id_to_key_name(key_id: int) -> str:
    return f'KEY{key_id:020}'

def code_template(seed: int, line_begin: str, line_end: str, assign_symbol: str, numeric_suffix: str):
    random = Random(seed)
    code_ops_count = 256
    code = ""
    code += f"{line_begin}{key_id_to_key_name(0)} {assign_symbol} (KEY + 0LLU){line_end}" + "\n"
    for target_key_id in range(1, code_ops_count):
        target = key_id_to_key_name(target_key_id)
        assign_symbol = '|'
        left_un_op = random.choice("+~-")
        left = key_id_to_key_name(target_key_id-1)
        op = random.choice("*^*^*^+-")
        right_un_op = random.choice("+~-")
        right = random.choice(
            [key_id_to_key_name(rand(0,target_key_id))] * int(log(target_key_id))
            + [f"{rand(10000000000000000000,2**64)}{numeric_suffix}"]
        )
        code += (
            f"{line_begin}{target} {assign_symbol} ( {left_un_op} {left} {op} {right_un_op} {right} ){line_end}"
        ) + "\n"
    code += f"{line_begin}RES {assign_symbol} {key_id_to_key_name(code_ops_count-1)}{line_end}" + '\n'
    return code

while 1:
    seed = Random()
    rc = 167772
    d: set[None] = set()
    nl = "\n"
    p2 = 2**64 - 1
    bs = "\\"
    open("task_gen_tmp.c", "w").write(
        f"""
#include <stdio.h>
#include <stdlib.h>
typedef long long unsigned llu;
int main(){{
    llu KEY={rand()}LLU;
    for (llu q=0;q<{rc};++q){{
        KEY ^= KEY << 21;
        KEY ^= KEY >> 35;
        KEY ^= KEY << 4;
        {code_template(seed, line_begin='        llu ', line_end=';', assign_symbol='=', numeric_suffix='LLU')}
        printf("%llx{bs}n",RES);
    }}
}}
"""
    )
    assert system("gcc -O2 task_gen_tmp.c -o task_gen_tmp.exe") == 0
    y = subprocess.run("./task_gen_tmp.exe", stdout=PIPE).stdout
    if len(set(y.split())) == rc:
        rc = 65536
        d = set()
        exec(
            f"""
for w in range(rc):
    KEY=rand()
    {code_template(seed, line_begin='    ', line_end=' & (2**64-1)', assign_symbol='=', numeric_suffix='')}
    d.add(RES)
"""
        )
        if len(d) == rc:
            break


print(
f"""
#include <stdio.h>
#include <stdlib.h>
typedef long long unsigned llu;
int main(){{
    char str[256];
    for (llu c=0; c<sizeof(str);++c){{
        str[c]=0;
    }}
    scanf("%255s", str);
    llu KEY=0;
    for (llu c=0; c<sizeof(str);++c){{
        KEY *= 257;
        KEY += (unsigned char)(str[c]);
    }}
    {code_template(seed, line_begin='        llu ', line_end=';', assign_symbol='=', numeric_suffix='LLU')}
    if (RES == {rand()}LLU){{
        printf("PASSWORD IS CORRECT{bs}n");
    }}else{{
        printf("PASSWORD IS INCORRECT{bs}n");
    }}
}}
"""
)
# print('llu ' code.replace(nl,';'+nl+'        llu ').replace('|','='))
# print(f"-DKEY={KEY}LLU")
# print(f"#if RES=={RES%2**64}LLU")

