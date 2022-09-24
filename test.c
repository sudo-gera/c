<<<<<<< HEAD
#include <stdio.h>


int main ()
{
    int y=260;
    asm(
        "mov x1,%[y]\n\t"

        "and w1,w1,255          \n\t"
        "mov w2,#1          \n\t"
        "loop:              \n\t"
        "cbz w1,skip        \n\t"
        "mul w2,w2,w1       \n\t"
        "sub w1,w1,#1       \n\t"
        "b loop             \n\t"
        "skip:              \n\t"

        "mov %[y],x2\n\t"
    :
        [y] "+r" (y)
    ::);
    printf("%i\n",y);
=======

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void run(int a[20]){
    printf("%i\n",a[0]);
    a[0]=3;
}

int main (int argc, char **argv){
    int a[20];
    a[0]=20;
    run(a);
    printf("%i\n",a[0]);
>>>>>>> e8212bd65ffb84b0985bedbcf2b207c5ecebb5f7
}
