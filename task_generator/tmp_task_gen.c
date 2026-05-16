
#include <stdio.h>
#include <stdlib.h>
typedef long long unsigned llu;
int main(){
    llu KEY=13065586037686516169LLU;
    for (llu q=0;q<167772;++q){
        KEY ^= KEY << 21;
        KEY ^= KEY >> 35;
        KEY ^= KEY << 4;

        llu KEY00000000000000000000 = (KEY + 0LLU);
        llu RES = KEY00000000000000000000;

        printf("%llx\n",RES);
    }
}
