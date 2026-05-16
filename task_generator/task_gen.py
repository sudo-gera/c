# from random import randint, choice
from random import Random
from math import log
from subprocess import PIPE
from os import system
import os
import subprocess
import textwrap

os.chdir(
    os.path.dirname(
        os.path.realpath(
            __file__
        )
    )
)

bs = "\\"
ln = "\n"

def key_id_to_key_name(key_id: int) -> str:
    return f'KEY{key_id:020}'

def code_template(seed: int, line_begin: str, line_end: str, assign_symbol: str, numeric_suffix: str) -> str:
    random = Random(seed)
    code_ops_count = 256
    code = ""
    code += f"{line_begin}{key_id_to_key_name(0)} {assign_symbol} (KEY + 0{numeric_suffix}){line_end}" + "\n"
    for target_key_id in range(1, code_ops_count):
        target = key_id_to_key_name(target_key_id)
        left_un_op = random.choice("+~-")
        left = key_id_to_key_name(target_key_id-1)
        op = random.choice("*^*^*^+-")
        right_un_op = random.choice("+~-")
        right = random.choice(
            [key_id_to_key_name(random.randint(0,target_key_id-1))] * int(log(target_key_id))
            + [f"{random.randint(10000000000000000000,2**64-1)}{numeric_suffix}"]
        )
        code += (
            f"{line_begin}{target} {assign_symbol} ( {left_un_op} {left} {op} {right_un_op} {right} ){line_end}"
        ) + "\n"
    code += f"{line_begin}RES {assign_symbol} {key_id_to_key_name(code_ops_count-1)}{line_end}" + '\n'
    return code

def is_injective(seed: int) -> bool:
    # injectivity test of this seed

    number_of_inputs = 167772
    open("tmp_task_gen.c", "w").write(
        textwrap.dedent(
            f"""
            #include <stdio.h>
            #include <stdlib.h>
            typedef long long unsigned llu;
            int main(){{
                llu KEY={Random().randint(0, 2**64-1)}LLU;
                for (llu q=0;q<{number_of_inputs};++q){{
                    KEY ^= KEY << 21;
                    KEY ^= KEY >> 35;
                    KEY ^= KEY << 4;
                    {ln+code_template(seed, line_begin='                    llu ', line_end=';', assign_symbol='=', numeric_suffix='LLU')}
                    printf("%llx{bs}n",RES);
                }}
            }}
            """
        )
    )
    assert system("gcc -O2 tmp_task_gen.c -o tmp_task_gen.exe") == 0
    c_test_stdout = subprocess.run("./tmp_task_gen.exe", stdout=PIPE).stdout
    if len(set(c_test_stdout.split())) != number_of_inputs:
        return False

    number_of_inputs = 65536
    results: set[int] = set()
    exec(
        textwrap.dedent(
            f"""
            import random
            for w in range({number_of_inputs}):
                KEY=random.randint(0, 2**64-1)
                {ln+code_template(seed, line_begin='                ', line_end=' & (2**64-1)', assign_symbol='=', numeric_suffix='')}
                results.add(RES)
            """
        ),
        dict(results=results),
    )
    if len(results) != number_of_inputs:
        return False

    return True

while 1:
    seed = Random().randint(0, 2**64-1)
    if is_injective(seed):
        break

print(
    textwrap.dedent(
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
            {ln+code_template(seed, line_begin='            llu ', line_end=';', assign_symbol='=', numeric_suffix='LLU')}
            if (RES == {Random().randint(0, 2**64-1)}LLU){{
                printf("ACCESS GRANTED{bs}n");
            }}else{{ // same length
                printf("WRONG PASSWORD{bs}n");
            }}
        }}
        """
    )
)
