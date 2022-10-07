<<<<<<< HEAD
#include <stdio.h>

int sum(int x0, size_t N, int *X){
    for (size_t w=0;w<N;++w){
        x0+=X[w];
    }
    return x0;
}


int main ()
{
<<<<<<< HEAD
    int y=260;
    asm(
        "mov x1,%[y]        \n\t"

        "and w1,w1,255      \n\t"
        "mov w2,#1          \n\t"
        "loop:              \n\t"
        "cbz w1,skip        \n\t"
        "mul w2,w2,w1       \n\t"
        "sub w1,w1,#1       \n\t"
        "b loop             \n\t"
        "skip:              \n\t"

        "mov %[y],x2        \n\t"
    :
        [y] "+r" (y)
    ::);
    printf("%i\n",y);
=======
>>>>>>> 383638390c3bd4b88bc2d793cc52e3e09def391f
}
=======
int main
>>>>>>> 37dd3845e25d15f427ae2869a98a9eb82732cf13
