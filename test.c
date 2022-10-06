#include <stdio.h>

int sum(int x0, size_t N, int *X){
    for (size_t w=0;w<N;++w){
        x0+=X[w];
    }
    return x0;
}


int main ()
{
}
