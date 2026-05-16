# from h import *

from random import randint, choice
from math import log
from subprocess import PIPE
from os import system
import subprocess


def rand(q: int = 2**64, e: int | None = None) -> int:
    if e is not None:
        q, e = e, q
    else:
        e = 0
    assert q - e
    return randint(e, q - 1)


while 1:
    code_ops_count = 256
    code = ""
    code += "\n" + (f"KEY{0:020} | (KEY + 0LLU)") + "\n"
    for w in range(1, code_ops_count):
        code += (
            f'KEY{w:020} | (KEY{w-1:020} {choice("*^*^*^+-")+" "+choice("+~-")} '
            + choice(
                [f"KEY{rand(0,w):020}"] * int(log(w))
                + [f"{rand(10000000000000000000,2**64)}LLU"]
            )
            + f")"
        ) + "\n"
    code += f"RES | KEY{code_ops_count-1:020}"
    rc = 167772
    d: set[None] = set()
    nl = "\n"
    p2 = 2**64 - 1
    bs = "\\"
    open("macrypt.c", "w").write(
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
        {code.replace(nl,';'+nl+'        llu ').replace('|','=')};
        printf("%llx{bs}n",RES);
    }}
}}
"""
    )
    assert system("gcc -O2 macrypt.c -o macrypt.exe") == 0
    y = subprocess.run("./macrypt.exe", stdout=PIPE).stdout
    if len(set(y.split())) == rc:
        rc = 65536
        d = set()
        exec(
            f"""
for w in range(rc):
    KEY=rand()
    {code[1:].replace('LLU','').replace('|','=').replace(nl,'&p2'+nl+'    ')}
    d.add(RES)
"""
        )
        if len(d) == rc:
            break


# print(code.replace("\n", "\n#define ").replace("|", ""))
# print(f"-DKEY={KEY}LLU")
# print(f"#if RES=={RES%2**64}LLU")

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
    {code.replace(nl,';'+nl+'    llu ').replace('|','=')};
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

