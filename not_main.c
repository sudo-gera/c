#include <stdio.h>
void caller(){
    printf("hello\n");
}

// int _start(){
//     __asm__ (
//         "nop\n"
//         "nop\n"
//         "mov $1234605616436508552,%rax\n"
//         "call *%rax\n"
//     );
//     return 0;
// }

const long long main[]={
    0xb8489090e5894855,
    (long long)caller,
    0x5d00000000b8d0ff,
    0x00000000801f0fc3,
};

