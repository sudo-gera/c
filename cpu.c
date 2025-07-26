#ifndef REGISTERS
#define REGISTERS 4
#endif

#include <stdio.h>
#include <stdlib.h>


int main(){
    unsigned char data[999999];
    while (1){
        int code = 0;
        scanf("%i", &code);
        if (code == 0){
            break;
        }
        if (code == 4){
            // printf("\n");
            for (size_t i = 0; i < REGISTERS; ++i){
                printf("%i ", data[i]);
            }
            printf("\n");
        }
        if (code == 1){
            int l = 0;
            scanf("%i", &l);
            int r = 0;
            scanf("%i", &r);
            data[l] += data[r];
        }
        if (code == 2){
            int l = 0;
            scanf("%i", &l);
            int r = 0;
            scanf("%i", &r);
            data[l] -= data[r];
        }
        if (code == 3){
            int l = 0;
            scanf("%i", &l);
            int r = 0;
            scanf("%i", &r);
            data[l] = r;
        }
    }
}
