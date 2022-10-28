void not_main();

void caller(){
    not_main();
}

// void __stack_chk_fail(){}

// extern void _f_printreg();


// const long long _start[]={
// const long long main[]={
//     0xb8489090e5894855,
//     (long long)caller,
//     0xc35d90909090d0ff,
// };


// int _start(){
//     __asm__ (
//         "nop\n"
//         "nop\n"
//         "mov $1234605616436508552,%rax\n"
//         "call *%rax\n"
//         "nop\n"
//         "nop\n"
//         "nop\n"
//     );


// // int main(){
//     __asm__ (
//         "lea -11(%rip),%rcx\n"
//     );
//     _f_printreg();
//     __asm__ (
//         "call *%rcx\n"
//     );
// }


// const char main[]="\x55\x48\x89\xe5\x48\x8b\x15\xda\x09\x20\x00\xb8\x00\x00\x00\x00\xff\xd2\xb8\x00\x00\x00\x00\x5d\xc3";

// char main[]={
//     0x55,
//     0x48, 0x89, 0xe5,
//     0x48, 0x8b, 0x15, 0xda, 0x09, 0x20, 0x00,
//     0xb8, 0x00, 0x00, 0x00, 0x00,
//     0xff, 0xd2,
//     0xb8, 0x00, 0x00, 0x00, 0x00,
//     0x5d,
//     0xc3,
// };

// void(*cp)()=caller;


#include <stdio.h>

long long unsigned count=0;

void not_main(){
    // _f_printreg();
    char data[20];
    sprintf(data,"%08llu  \r",count++);
    printf("%s",data);
}